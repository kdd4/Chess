#pragma once

#include <exception>

namespace Chess
{
    class Figure;
    class Board;

    struct Position
    {
        Position();
        Position(int x, int y);
        int x = -1;
        int y = -1;

        bool operator==(const Position& right);
        bool operator!=(const Position& right);
        bool check() const;
    };

    struct Move
    {
        Move(Position movePos, Position attackedPos);
        Move(Position movePos);
        Move();
        Position movePos;
        Position attackedPos;
    };

    namespace Color
    {
        enum Color : int {Black = -1, Null, White = 1, Both};
    }

    namespace Figures
    {
        enum class Type : int {Null, Pawn, Rook, Knight, Bishop, Queen, King};
    }

    struct excLogicalError : public std::exception
    {
        const char* what() const noexcept override;
    };
}

