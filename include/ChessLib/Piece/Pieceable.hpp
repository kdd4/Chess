#pragma once

#include "ChessLib/Piece/Type.hpp"

#include <vector>

namespace Chess
{
    class Pieceable
    {
        PieceType type = PieceType::Null;
        PieceColor color = PieceColor::Null;

        std::vector<int> lastMoveMoment = { -1 };
        int moveCount = 0;
        bool deleted = false;
    };
}