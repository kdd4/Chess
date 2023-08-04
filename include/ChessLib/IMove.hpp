#pragma once

#include "ChessLib/IBoard.hpp"

#include <vector>

namespace Chess
{
    class IMove
    {
    public:
        virtual void make(IBoard*) = 0;
        virtual void cancel(IBoard*) = 0;
    };
}
