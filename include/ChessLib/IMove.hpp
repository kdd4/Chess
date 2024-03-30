#pragma once

#include <vector>

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

#include <map>
#include <set>

namespace Chess
{
    class IMove
    {
    public:
        virtual void make() = 0;
        virtual void cancel() = 0;

        virtual const std::map<Position, Position>& getSteps() const = 0;
        virtual const std::set<Position>& getAttackedPositions() const = 0;
        virtual const std::map<Position, PieceType>& getTypeChanges() const = 0;
    };
}
