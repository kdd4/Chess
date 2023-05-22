#pragma once

namespace Chess
{
    struct Position
    {
        Position();
        Position(short int x, short int y);
        Position(const Position& right);
        short int x;
        short int y;

        bool operator==(const Position& right) const;
        bool operator!=(const Position& right) const;
        bool check() const;
    };
}
