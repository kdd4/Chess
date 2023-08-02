#include "ChessLib/Figures/Queen.hpp"

namespace Chess
{
    namespace Figures
    {
        Queen::Queen(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Queen, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}

        Figure* Queen::clone(Board* board) const
        {
            return new Queen(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        void Queen::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            // X+
            for (int x = pos.x + 1; x < 8; ++x)
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
            for (int x = pos.x - 1; x >= 0; --x)
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
            for (int y = pos.y + 1; y < 8; ++y)
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
            for (int y = pos.y - 1; y >= 0; --y)
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
                Position movePos(pos.x + i, pos.y + i);
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
                Position movePos(pos.x + i, pos.y - i);
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
                Position movePos(pos.x - i, pos.y + i);
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
                Position movePos(pos.x - i, pos.y - i);
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
    }
}