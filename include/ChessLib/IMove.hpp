#pragma once

#include "ChessLib/IBoard.hpp"

namespace Chess
{
    class IMove
    {
    public:
        virtual void make(IBoard*) = 0;
        virtual void cancel(IBoard*) = 0;
    };
}