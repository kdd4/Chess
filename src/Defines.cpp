#include "Chess/Defines.hpp"

namespace Chess
{
    Position::Position() {};
    Position::Position(int x, int y) : x(x), y(y) {};

    bool Position::operator==(const Position& right)
    {
        return (x == right.x && y == right.y);
    }

    bool Position::operator!=(const Position& right)
    {
        return !(x == right.x && y == right.y);
    }

    bool Position::check() const
    {
        return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
    }

    Move::Move(Position movePos, Position attackedPos) : movePos(movePos), attackedPos(attackedPos) {};
    Move::Move(Position movePos) : movePos(movePos), attackedPos(movePos) {};
    Move::Move() {};

    const char* excLogicalError::what() const noexcept
    {
        return "Detecting a logical error in code";
    }
}
