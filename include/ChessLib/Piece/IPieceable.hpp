#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

#include <vector>

namespace Chess
{
    class IPieceable
    {
    public:
        IPieceable(Position pos, PieceType type, PieceColor color, std::vector<int> moveMoment={}, bool deleted=false);
        IPieceable(const IPieceable& right);

        int getDirection() const;
        int getLastMoveMoment() const;
        int getMoveCount() const;

        Position pos;

        PieceType type = PieceType::Null;
        PieceColor color = PieceColor::Null;

        std::vector<int> moveMoment;
        bool deleted = false;
    };
}