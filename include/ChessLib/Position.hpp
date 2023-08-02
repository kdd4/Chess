#pragma once

namespace Chess
{
    struct Position
    {
        int x;
        int y;

        Position();
        Position(int x, int y);
        Position(const Position& right);

        bool operator==(const Position& right) const;
        bool operator!=(const Position& right) const;

        bool check() const;
    };
}
