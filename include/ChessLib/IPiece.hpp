#pragma once

#include "Position.hpp"
#include "Defines.hpp"

#include <vector>

namespace Chess
{
    class Piece
    {
    public:
        virtual Piece* clone(Board* board) const = 0;
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
