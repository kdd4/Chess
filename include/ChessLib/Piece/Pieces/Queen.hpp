#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Move.hpp"

#include <vector>

namespace Chess
{
    namespace Piece
    {
        class Queen : public IPiece
        {
        public:
            Queen(Position pos, PieceColor color, IBoard* board);
            Queen(IPieceable* data, IAllocatable* loc);
            Queen(const IPiece& right);

            IPiece* clone(IBoard* board) const override final;
            void getMoves(std::vector<Move*>& vec, bool onlyAttack = false) const override final;
        };
    }
}
