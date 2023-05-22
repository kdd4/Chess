#pragma once

#include <exception>

namespace Chess
{
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

