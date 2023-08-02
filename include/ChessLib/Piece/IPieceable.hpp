#pragma once

#include "ChessLib/Piece/Enums.hpp"

#include <vector>

namespace Chess
{
    class IPieceable
    {
    public:
        Position pos;

        PieceType type = PieceType::Null;
        PieceColor color = PieceColor::Null;

        std::vector<int> lastMoveMoment = { -1 };
        int moveCount = 0;
        bool deleted = false;
    };
}