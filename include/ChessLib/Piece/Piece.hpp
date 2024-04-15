#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

#include <vector>

namespace Chess
{
    class IPiece
    {
    public:
        IPiece(Position pos, PieceType type, PieceColor color, std::vector<int> moveMoment={}, bool deleted=false);
        IPiece(const IPiece& right);

        int getDirection() const;
        int getLastMoveMoment() const;
        int getMoveCount() const;

        void addMoveCount(int moveCnt);
        void delMoveCount();

        Position pos;

        PieceType type = PieceType::Null;
        PieceColor color = PieceColor::Null;

        std::vector<int> moveMoment;
        bool deleted = false;
    };

    typedef IPiece Piece;
}