#include "ChessLib/Figures/King.hpp"

namespace Chess
{
    namespace Figures
    {
        King::King(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::King, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}

        Figure* King::clone(Board* board) const
        {
            return new King(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        void King::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            for (int ix = -1; ix <= 1; ++ix)
            {
                for (int iy = -1; iy <= 1; ++iy)
                {
                    Position movePos(pos.x + ix, pos.y + iy);
                    if ((ix == 0 && iy == 0) || !movePos.check()) continue;
                    Figure* attackedFigure = board->getFigure(movePos);
                    if (attackedFigure != nullptr)
                    {
                        if (attackedFigure->color != color)
                            vec.push_back(Move(this, movePos));
                    }
                    else
                        vec.push_back(Move(this, movePos));
                }
            }

            if (moveCount != 0) return;

            if (!onlyAttack)
            {
                QueensideCastling(vec);
                KingsideCastling(vec);
            }
        }

        void King::QueensideCastling(std::vector<Move>& vec) const
        {
            if (moveCount != 0) return;

            Figure* figureRook = board->getFigure(Position(0, pos.y));
            if (figureRook == nullptr) return;
            if (figureRook->type != Figures::Type::Rook || figureRook->color != color || figureRook->moveCount != 0) return;

            for (int x = pos.x - 1; x > 0; --x)
            {
                if (board->getFigure(Position(x, pos.y)) != nullptr) return;
            }

            Position pos1 = Position(pos.x - 1, pos.y);
            Position pos2 = Position(pos.x - 2, pos.y);

            std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, color * (-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (mv.attackedFigure == nullptr) continue;
                if (pos1 == mv.attackedFigure->pos || pos2 == mv.attackedFigure->pos) return;
            }

            Move moving(this, Position(pos.x - 2, pos.y), nullptr);
            moving.addAdditionalMove(MoveEvent(figureRook, Position(pos.x - 1, pos.y)));
            vec.push_back(moving);
        }

        void King::KingsideCastling(std::vector<Move>& vec) const
        {
            if (moveCount != 0) return;

            Figure* figureRook = board->getFigure(Position(7, pos.y));
            if (figureRook == nullptr) return;
            if (figureRook->type != Figures::Type::Rook || figureRook->color != color || figureRook->moveCount != 0) return;

            for (int x = pos.x + 1; x < 7; ++x)
            {
                if (board->getFigure(Position(x, pos.y)) != nullptr) return;
            }

            Position pos1 = Position(pos.x + 1, pos.y);
            Position pos2 = Position(pos.x + 2, pos.y);

            std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, color * (-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (mv.attackedFigure == nullptr) continue;
                if (pos1 == mv.attackedFigure->pos || pos2 == mv.attackedFigure->pos) return;
            }

            Move moving(this, Position(pos.x + 2, pos.y), nullptr);
            moving.addAdditionalMove(MoveEvent(figureRook, Position(pos.x + 1, pos.y)));
            vec.push_back(moving);
        }
    }
}