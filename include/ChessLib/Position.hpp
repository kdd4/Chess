#pragma once

namespace Chess
{
    struct Position
    {
        Position();
        Position(int x, int y);
        Position(const Position& right);
        int x;
        int y;

        bool operator==(const Position& right) const;
        bool operator!=(const Position& right) const;
        bool check() const;
    };
}
