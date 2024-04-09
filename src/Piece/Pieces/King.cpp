#include "ChessLib/Piece/Pieces/King.hpp"

namespace Chess
{
    namespace Pieces
    {
        King::King(Position pos, PieceColor color, std::weak_ptr<Board>& board)
            :
            MovablePiece(pos, PieceType::King, color, board)
        {}

        King::King(Piece& piece, std::weak_ptr<Board>& board)
            :
            MovablePiece(piece, board)
        {
            type = PieceType::King;
        }

        King::King(MovablePiece& right)
            :
            MovablePiece(right)
        {
            type = PieceType::King;
        }

        std::shared_ptr<MovablePiece> King::clone(std::weak_ptr<Board> board) const
        {
            return std::make_shared<MovablePiece>(new King((Piece)*this, board));
        }

        void King::getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack) const
        {
            if (this->deleted) return;

            std::shared_ptr<ImplMove> move;
            std::shared_ptr<Piece> attacked_place;
            Position move_step;

            for (int ix = -1; ix <= 1; ++ix)
            {
                for (int iy = -1; iy <= 1; ++iy)
                {
                    move_step = {pos.x + ix, pos.y + iy };
                    if ((ix == 0 && iy == 0) || !move_step.check()) continue;

                    attacked_place = board.lock()->getPiece(move_step);
                    if (attacked_place != nullptr)
                    {
                        if (attacked_place->color == color)
                            continue;
                    }
                    
                    move = std::make_shared<ImplMove>(new ImplMove(board));
                    move->appendStep(pos, move_step);
                    move->appendAttack(move_step);
                    vec.push_back(move);
                }
            }

            if (this->getMoveCount() != 0) return;

            if (!onlyAttack)
            {
                QueensideCastling(vec);
                KingsideCastling(vec);
            }
        }

        void King::QueensideCastling(std::vector<std::shared_ptr<Move>>& vec) const
        {
            if (this->getMoveCount() != 0) return;

            std::shared_ptr<Piece> figureRook = board.lock()->getPiece(Position(0, pos.y));
            if (figureRook == nullptr) return;
            if (figureRook->type != PieceType::Rook ||\
                figureRook->color != color ||\
                figureRook->getMoveCount() != 0) return;

            for (int x = pos.x - 1; x > 0; --x)
            {
                if (board.lock()->getPiece(Position(x, pos.y)) != nullptr) return;
            }

            Position pos1 = Position(pos.x - 1, pos.y);
            Position pos2 = Position(pos.x - 2, pos.y);

            std::vector<Move> enemyMoves = board.lock()->getMoves(board->findFigures(Figures::Type::Null, color * (-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (mv.attackedFigure == nullptr) continue;
                if (pos1 == mv.attackedFigure->pos || pos2 == mv.attackedFigure->pos) return;
            }

            Move moving(this, Position(pos.x - 2, pos.y), nullptr);
            moving.addAdditionalMove(MoveEvent(figureRook, Position(pos.x - 1, pos.y)));
            vec.push_back(moving);
        }

        void King::KingsideCastling(std::vector<std::shared_ptr<Move>>& vec) const
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