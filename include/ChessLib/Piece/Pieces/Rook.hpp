#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Move.hpp"

#include <vector>

namespace Chess
{
    namespace Piece
    {
        class Rook : public IPiece
        {
        public:
            Rook(Position pos, PieceColor color, IBoard* board);
            Rook(IPieceable* data, IAllocatable* loc);
            Rook(const IPiece& right);

            IPiece* clone(IBoard* board) const override final;
            void getMoves(std::vector<IMove*>& vec, bool onlyAttack = false) const override final;
        };
    }
}
