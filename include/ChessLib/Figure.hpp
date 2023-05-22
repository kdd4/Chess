#pragma once

#include "Position.hpp"
#include "Defines.hpp"

#include <vector>


namespace Chess
{
    class Board;
    struct Move;

    class Figure
    {
    public:
        Figure(Position position, int color, Figures::Type type, Chess::Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted);
        virtual ~Figure();
        virtual Figure* clone(Board* board) const = 0;
        virtual void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const = 0;

        Position pos;
        int color = Color::Null;
        int lastMoveMoment = -1;
        int prevLastMoveMoment = -1;
        int moveCount = 0;
        bool deleted = false;
        Board* board;
        Figures::Type type;
    };
}
