#include "ChessLib/Position.hpp"

namespace Chess
{
    Position::Position() :
        x(0),
        y(0)
    {}

    Position::Position(int x, int y) :
        x(x),
        y(y)
    {}

    Position::Position(const Position& right) :
        x(right.x),
        y(right.y)
    {}

    bool Position::operator==(const Position& right) const
    {
        return (x == right.x && y == right.y);
    }

    bool Position::operator!=(const Position& right) const
    {
        return !(x == right.x && y == right.y);
    }

    bool Position::operator<(const Position& right) const
    {
        return (y == right.y) ? x < right.x : y < right.y;
    }

    bool Position::check() const
    {
        return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
    }
}
