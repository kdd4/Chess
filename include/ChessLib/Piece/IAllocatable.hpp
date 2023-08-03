#pragma once

#include "ChessLib/IBoard.hpp"
#include "ChessLib/Position.hpp"

namespace Chess
{
    class IAllocatable
    {
    public:
        IAllocatable(IBoard* board);
        IAllocatable(const IAllocatable& right);

        IBoard* board;
    };
}