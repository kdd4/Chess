#pragma once

#include "IMove.hpp"
#include "Position.hpp"
#include "Board.hpp"

#include <map>

namespace Chess
{
    class MoveImpl : public IMove
    {
    public:
        MoveImpl();

        void make(Board*) override;
        void cancel(Board*) override;
        void append();

    private:
        std::map<Position, Position> steps;
        
    };
}
