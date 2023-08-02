#include "ChessLib/Figures/Pawn.hpp"

namespace Chess
{
    namespace Figures
    {
        Pawn::Pawn(Position position, int color, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) 
            : 
            Figure(position, color, Figures::Type::Pawn, board, moveCount, lastMoveMoment, prevLastMoveMoment, deleted) 
        {}

        Figure* Pawn::clone(Board* board) const
        {
            return new Pawn(this->pos, this->color, board, this->moveCount, this->lastMoveMoment, this->prevLastMoveMoment, this->deleted);
        }

        void Pawn::getMoves(std::vector<Move>& vec, bool onlyAttack) const
        {
            if (deleted) return;
            if (pos.y + color >= 8 || pos.y + color < 0) return;
            Position movePos = Position(pos.x, pos.y + color);
            const Figure* figure = board->getFigure(movePos);
            if (figure == nullptr && !onlyAttack)
            {
                vec.push_back(Move(this, movePos, nullptr));
                movePos = Position(pos.x, pos.y + color * 2);
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
                movePos = Position(pos.x + 1, pos.y + color);
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
                    figure = board->getFigure(Position(pos.x + 1, pos.y));
                    if (figure != nullptr)
                    {
                        if (figure->color != color && figure->type == Figures::Type::Pawn)
                        {
                            if (figure->moveCount == 1 && figure->lastMoveMoment + 1 == board->moveCounter)
                                vec.push_back(Move(this, Position(pos.x + 1, pos.y + color), Position(pos.x + 1, pos.y)));
                        }
                    }
                }
            }

            if (pos.x != 0)
            {
                movePos = Position(pos.x - 1, pos.y + color);
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
                    figure = board->getFigure(Position(pos.x - 1, pos.y));
                    if (figure != nullptr)
                    {
                        if (figure->color != color && figure->type == Figures::Type::Pawn)
                        {
                            if (figure->moveCount == 1 && figure->lastMoveMoment + 1 == board->moveCounter)
                                vec.push_back(Move(this, Position(pos.x - 1, pos.y + color), Position(pos.x - 1, pos.y)));
                        }
                    }
                }
            }
        }

    }
}