#include "Chess/Figures.hpp"

namespace Chess
{
    Figure::Figure(Position position, int color, Figures::Type type, Board* board, int moveCount, int lastMoveMoment, bool deleted)
    : pos(position), color(color), lastMoveMoment(lastMoveMoment), moveCount(moveCount), deleted(deleted), board(board), type(type)
    {}

    Figure::~Figure() {};

    namespace Figures
    {
        Pawn::Pawn(Position position, int color, Board* board, int moveCount, int lastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Pawn, board, moveCount, lastMoveMoment, deleted) {}
        Rook::Rook(Position position, int color, Board* board, int moveCount, int lastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Rook, board, moveCount, lastMoveMoment, deleted) {}
        Knight::Knight(Position position, int color, Board* board, int moveCount, int lastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Knight, board, moveCount, lastMoveMoment, deleted) {}
        Bishop::Bishop(Position position, int color, Board* board, int moveCount, int lastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Bishop, board, moveCount, lastMoveMoment, deleted) {}
        Queen::Queen(Position position, int color, Board* board, int moveCount, int lastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Queen, board, moveCount, lastMoveMoment, deleted) {}
        King::King(Position position, int color, Board* board, int moveCount, int lastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::King, board, moveCount, lastMoveMoment, deleted) {}

        Figure* Pawn::clone(Board* board) const
        {
            return new Pawn(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->deleted);
        }

        Figure* Rook::clone(Board* board) const
        {
            return new Rook(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->deleted);
        }

        Figure* Knight::clone(Board* board) const
        {
            return new Knight(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->deleted);
        }

        Figure* Bishop::clone(Board* board) const
        {
            return new Bishop(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->deleted);
        }

        Figure* Queen::clone(Board* board) const
        {
            return new Queen(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->deleted);
        }

        Figure* King::clone(Board* board) const
        {
            return new King(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->deleted);
        }

        void Pawn::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            if (deleted) return;
            if (pos.y+color >= 8 || pos.y+color < 0) return;
            Position movePos = Position(pos.x, pos.y+color);
            const Figure* figure = board->getFigure(movePos);
            if (figure == nullptr && !onlyAttack)
            {
                vec.push_back(Move(movePos, Position()));
                if (this->lastMoveMoment == -1 && (pos.y+color*2 < 8 && pos.y+color*2 >= 0))
                {
                    movePos = Position(pos.x, pos.y+color*2);
                    figure = board->getFigure(movePos);
                    if (figure == nullptr)
                    {
                        vec.push_back(Move(movePos, Position()));
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
                        vec.push_back(Move(movePos));
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
                                vec.push_back(Move(Position(pos.x+1, pos.y+color), Position(pos.x+1, pos.y)));
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
                        vec.push_back(Move(movePos));
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
                                vec.push_back(Move(Position(pos.x-1, pos.y+color), Position(pos.x-1, pos.y)));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
            }

            // X-
            for (int x = pos.x-1; x >= 0; --x)
            {
                Position movePos(x, pos.y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
            }

            // Y+
            for (int y = pos.y+1; y < 8; ++y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
            }

            // Y-
            for (int y = pos.y-1; y >= 0; --y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }


            movePos = Position(pos.x+2, pos.y-1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }

            movePos = Position(pos.x-2, pos.y+1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }

            movePos = Position(pos.x-2, pos.y-1);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }

            movePos = Position(pos.x+1, pos.y+2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }

            movePos = Position(pos.x+1, pos.y-2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }

            movePos = Position(pos.x-1, pos.y+2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
            }

            movePos = Position(pos.x-1, pos.y-2);
            if (movePos.check())
            {
                attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                }
                else
                    vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
            }

            // X-
            for (int x = pos.x-1; x >= 0; --x)
            {
                Position movePos(x, pos.y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
            }

            // Y+
            for (int y = pos.y+1; y < 8; ++y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
            }

            // Y-
            for (int y = pos.y-1; y >= 0; --y)
            {
                Position movePos(pos.x, y);
                Figure* attackedFigure = board->getFigure(movePos);
                if (attackedFigure != nullptr)
                {
                    if (attackedFigure->color != color)
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                        vec.push_back(Move(movePos));
                    break;
                }
                vec.push_back(Move(movePos));
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
                            vec.push_back(Move(movePos));
                    }
                    else
                        vec.push_back(Move(movePos));
                }
            }

            if (moveCount != 0) return;
            if (!onlyAttack)
            {
                if (LeftCastling()) vec.push_back(Move(Position(pos.x-2, pos.y), Position()));
                if (RightCastling()) vec.push_back(Move(Position(pos.x+2, pos.y), Position()));
            }
        }

        bool King::LeftCastling() const
        {
            if (moveCount != 0) return false;

            Figure* figure = board->getFigure(Position(0, pos.y));
            if (figure == nullptr) return false;
            if (figure->type != Figures::Type::Rook || figure->color != color || figure->moveCount != 0) return false;

            for (int x = pos.x-1; x > 0; --x)
            {
                if (board->getFigure(Position(x, pos.y)) != nullptr) return false;
            }

            Position pos1 = Position(pos.x - 1, pos.y);
            Position pos2 = Position(pos.x - 2, pos.y);

            std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, color*(-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (pos1 == mv.attackedPos || pos2 == mv.attackedPos) return false;
            }
            return true;
        }

        bool King::RightCastling() const
        {
            if (moveCount != 0) return false;

            Figure* figure = board->getFigure(Position(7, pos.y));
            if (figure == nullptr) return false;
            if (figure->type != Figures::Type::Rook || figure->color != color || figure->moveCount != 0) return false;

            for (int x = pos.x+1; x < 7; ++x)
            {
                if (board->getFigure(Position(x, pos.y)) != nullptr) return false;
            }

            Position pos1 = Position(pos.x + 1, pos.y);
            Position pos2 = Position(pos.x + 2, pos.y);

            std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, color*(-1)), true);
            for (Move& mv : enemyMoves)
            {
                if (pos1 == mv.attackedPos || pos2 == mv.attackedPos) return false;
            }
            return true;
        }
    }
}

