#pragma once

#include "ChessLib/IBoard.hpp"
#include "ChessLib/Position.hpp"

namespace Chess
{
    class IAllocatable
    {
    public:
        IBoard* board;
    };
}