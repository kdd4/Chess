#pragma once

#include "Position.hpp"
#include "Figure.hpp"
#include "Board.hpp"

#include <vector>

namespace Chess
{
    struct MoveEvent
    {
        MoveEvent();
        MoveEvent(const Figure* figure, const Position& newPos);

        const Figure* figure;
        Position figurePos;
        Position newPos;
    };

    struct Move
    {
        Move();
        Move(const Figure* figure, const Position& newPos);
        Move(const Figure* figure, const Position& newPos, const Position& attackedPos);
        Move(const Figure* figure, const Position& newPos, Figure* attackedFigure);

        void addAdditionalMove(MoveEvent event);

        Figure* attackedFigure;
        MoveEvent moving;
        std::vector<MoveEvent> additionalMoving;
    };
}
