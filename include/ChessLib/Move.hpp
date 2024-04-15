#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

#include <map>
#include <set>

namespace Chess
{
    class IMove
    {
    public:
        virtual const std::map<Position, Position>& getSteps() const = 0;
        virtual const std::set<Position>& getAttackedPositions() const = 0;
        virtual const std::map<Position, std::pair<PieceType, PieceType>>& getTypeChanges() const = 0; // old and new types

        virtual int getMoveCount() const = 0;
    };

    typedef IMove Move;
}


