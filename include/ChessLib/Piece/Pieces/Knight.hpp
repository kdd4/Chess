#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Move.hpp"

#include <vector>

namespace Chess
{
    namespace Piece
    {
        class Knight : public IPiece
        {
        public:
            Knight(Position pos, PieceColor color, IBoard* board);
            Knight(IPieceable* data, IAllocatable* loc);
            Knight(const IPiece& right);

            IPiece* clone(IBoard* board) const override final;
            void getMoves(std::vector<Move*>& vec, bool onlyAttack = false) const override final;
        };
    }
}
