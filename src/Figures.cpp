#include "Chess/Figures.hpp"

namespace Chess
{
    namespace Figures
    {
        Pawn::Pawn(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Pawn, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}
        Rook::Rook(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Rook, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}
        Knight::Knight(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Knight, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}
        Bishop::Bishop(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Bishop, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}
        Queen::Queen(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Queen, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}
        King::King(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::King, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}

        Figure* Pawn::clone(Board* board) const
        {
            return new Pawn(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        Figure* Rook::clone(Board* board) const
        {
            return new Rook(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        Figure* Knight::clone(Board* board) const
        {
            return new Knight(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        Figure* Bishop::clone(Board* board) const
        {
            return new Bishop(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        Figure* Queen::clone(Board* board) const
        {
            return new Queen(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        Figure* King::clone(Board* board) const
        {
            return new King(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        void Pawn::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            if (deleted) return;
            if (pos.y+color >= 8 || pos.y+color < 0) return;
            Position movePos = Position(pos.x, pos.y+color);
            const Figure* figure = board->getFigure(movePos);
            if (figure == nullptr && !onlyAttack)
            {
                vec.push_back(Move(this, movePos, nullptr));
                movePos = Position(pos.x, pos.y+color*2);
                if (this->lastMoveMoment == -1 && movePos.check())
                {
                    figure = board->getFigure(movePos);
                    if (figure == nullptr)
                    {
                        vec.push_back(Move(this, movePos, nullptr));
                    }
                }
            }

            if (pos.x != 7)
            {
                movePos = Position(pos.x+1, pos.y+color);
                figure = board->getFigure(movePos);
                if (figure != nullptr)
                {
                    if (figure->color != color)
                    {
                        vec.push_back(Move(this, movePos));
                    }
                }
                else
                {
                    figure = board->getFigure(Position(pos.x+1, pos.y));
                    if (figure != nullptr)
                    {
                        if (figure->color != color && figure->type == Figures::Type::Pawn)
                        {
                            if (figure->moveCount == 1 && figure->lastMoveMoment+1 == board->moveCounter)
                                vec.push_back(Move(this, Position(pos.x+1, pos.y+color), Position(pos.x+1, pos.y)));
                        }
                    }
                }
            }

            if (pos.x != 0)
            {
                movePos = Position(pos.x-1, pos.y+color);
                figure = board->getFigure(movePos);
                if (figure != nullptr)
                {
                    if (figure->color != color)
                    {
                        vec.push_back(Move(this, movePos));
                    }
                }
                else
                {
                    figure = board->getFigure(Position(pos.x-1, pos.y));
                    if (figure != nullptr)
                    {
                        if (figure->color != color && figure->type == Figures::Type::Pawn)
                        {
                            if (figure->moveCount == 1 && figure->lastMoveMoment+1 == board->moveCounter)
                                vec.push_back(Move(this, Position(pos.x-1, pos.y+color), Position(pos.x-1, pos.y)));
                        }
                    }
                }
            }
        }

        void Rook::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            // X+
            for (int x = pos.x+1; x < 8; ++x)
            {
                Position movePos(x, pos.y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X-
            for (int x = pos.x-1; x >= 0; --x)
            {
                Position movePos(x, pos.y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // Y+
            for (int y = pos.y+1; y < 8; ++y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // Y-
            for (int y = pos.y-1; y >= 0; --y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }
        }

        void Knight::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            Position movePos;
            Figure* attackedFigure;

            movePos = Position(pos.x+2, pos.y+1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }


            movePos = Position(pos.x+2, pos.y-1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }

            movePos = Position(pos.x-2, pos.y+1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }

            movePos = Position(pos.x-2, pos.y-1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }

            movePos = Position(pos.x+1, pos.y+2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }

            movePos = Position(pos.x+1, pos.y-2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }

            movePos = Position(pos.x-1, pos.y+2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }

            movePos = Position(pos.x-1, pos.y-2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                }
                else
                    vec.push_back(Move(this, movePos));
            }
        }

        void Bishop::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            // X+Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x+i, pos.y+i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X+Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x+i, pos.y-i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X-Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x-i, pos.y+i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X-Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x-i, pos.y-i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }
        }

        void Queen::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            // X+
            for (int x = pos.x+1; x < 8; ++x)
            {
                Position movePos(x, pos.y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X-
            for (int x = pos.x-1; x >= 0; --x)
            {
                Position movePos(x, pos.y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // Y+
            for (int y = pos.y+1; y < 8; ++y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // Y-
            for (int y = pos.y-1; y >= 0; --y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X+Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x+i, pos.y+i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X+Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x+i, pos.y-i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X-Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x-i, pos.y+i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }

            // X-Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x-i, pos.y-i);
                if (!movePos.check()) break;
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(this, movePos));
                    break;
                }
                vec.push_back(Move(this, movePos));
            }
        }

        void King::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            for (int ix = -1; ix <= 1; ++ix)
            {
                for (int iy = -1; iy <= 1; ++iy)
                {
                    Position movePos(pos.x+ix, pos.y+iy);
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
                LeftCastling(vec);
                RightCastling(vec);
            }
        }

        void King::LeftCastling(std::vector<Move>& vec) const
        {
            if (moveCount != 0) return;

            Figure* figureRook = board->getFigure(Position(0, pos.y));
            if (figureRook == nullptr) return;
            if (figureRook->type != Figures::Type::Rook || figureRook->color != color || figureRook->moveCount != 0) return;

            for (int x = pos.x-1; x > 0; --x)
            {
                if (board->getFigure(Position(x, pos.y)) != nullptr) return;
            }

            Position pos1 = Position(pos.x - 1, pos.y);
            Position pos2 = Position(pos.x - 2, pos.y);

            std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, color*(-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (mv.attackedFigure == nullptr) continue;
                if (pos1 == mv.attackedFigure->pos || pos2 == mv.attackedFigure->pos) return;
            }

            Move moving(this, Position(pos.x-2, pos.y), nullptr);
            moving.addAdditionalMove(MoveEvent(figureRook, Position(pos.x-1, pos.y)));
            vec.push_back(moving);
        }

        void King::RightCastling(std::vector<Move>& vec) const
        {
            if (moveCount != 0) return;

            Figure* figureRook = board->getFigure(Position(7, pos.y));
            if (figureRook == nullptr) return;
            if (figureRook->type != Figures::Type::Rook || figureRook->color != color || figureRook->moveCount != 0) return;

            for (int x = pos.x+1; x < 7; ++x)
            {
                if (board->getFigure(Position(x, pos.y)) != nullptr) return;
            }

            Position pos1 = Position(pos.x + 1, pos.y);
            Position pos2 = Position(pos.x + 2, pos.y);

            std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, color*(-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (mv.attackedFigure == nullptr) continue;
                if (pos1 == mv.attackedFigure->pos || pos2 == mv.attackedFigure->pos) return;
            }

            Move moving(this, Position(pos.x+2, pos.y), nullptr);
            moving.addAdditionalMove(MoveEvent(figureRook, Position(pos.x+1, pos.y)));
            vec.push_back(moving);
        }
    }
}

