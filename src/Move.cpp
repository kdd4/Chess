#include "Chess/Move.hpp"

namespace Chess
{
    MoveEvent::MoveEvent() :
        figure(nullptr),
        figurePos(),
        newPos()
    {}

    MoveEvent::MoveEvent(const Figure* figure, const Position& newPos) :
        figure(figure),
        figurePos(figure->pos),
        newPos(newPos)
    {}


    Move::Move() :
        attackedFigure(nullptr),
        moving(),
        additionalMoving()
    {}

    Move::Move(const Figure* figure, const Position& newPos) :
        attackedFigure(figure->board->getFigure(newPos)),
        moving(MoveEvent(figure, newPos)),
        additionalMoving()
    {}

    Move::Move(const Figure* figure, const Position& newPos, const Position& attackedPos) :
        attackedFigure(figure->board->getFigure(attackedPos)),
        moving(MoveEvent(figure, newPos)),
        additionalMoving()
    {}

    Move::Move(const Figure* figure, const Position& newPos, Figure* attackedFigure) :
        attackedFigure(attackedFigure),
        moving(MoveEvent(figure, newPos)),
        additionalMoving()
    {}

    void Move::addAdditionalMove(MoveEvent event)
    {
        additionalMoving.push_back(event);
    }
}
