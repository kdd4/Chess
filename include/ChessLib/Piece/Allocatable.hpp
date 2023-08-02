#pragma once

#include "ChessLib/IBoard.hpp"
#include "ChessLib/Position.hpp"

namespace Chess
{
    class Allocatable
    {
        IBoard* board;
        Position pos;
    };
}