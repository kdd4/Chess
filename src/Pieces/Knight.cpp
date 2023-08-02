#include "ChessLib/Figures/Knight.hpp"

namespace Chess
{
    namespace Figures
    {
        Knight::Knight(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted)
            :
            Figure(position, color, Figures::Type::Knight, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted)
        {}

        Figure* Knight::clone(Board* board) const
        {
            return new Knight(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        void Knight::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            Position movePos;
            Figure* attackedFigure;

            movePos = Position(pos.x + 2, pos.y + 1);
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


            movePos = Position(pos.x + 2, pos.y - 1);
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

            movePos = Position(pos.x - 2, pos.y + 1);
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

            movePos = Position(pos.x - 2, pos.y - 1);
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

            movePos = Position(pos.x + 1, pos.y + 2);
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

            movePos = Position(pos.x + 1, pos.y - 2);
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

            movePos = Position(pos.x - 1, pos.y + 2);
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

            movePos = Position(pos.x - 1, pos.y - 2);
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

    }
}