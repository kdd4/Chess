#pragma once

#include "Board.hpp"

namespace Chess
{
    class IMove
    {
    public:
        virtual void make(Board*) = 0;
        virtual void cancel(Board*) = 0;
    };
}