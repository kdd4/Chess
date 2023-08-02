#include "ChessLib/Figures/Bishop.hpp"

namespace Chess
{
    namespace Figures
    {
        Bishop::Bishop(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) : Figure(position, color, Figures::Type::Bishop, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) {}
        
        Figure* Bishop::clone(Board* board) const
        {
            return new Bishop(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        void Bishop::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
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