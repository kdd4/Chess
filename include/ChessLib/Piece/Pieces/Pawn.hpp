#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/Board.hpp"
#include "ChessLib/IMove.hpp"

#include <vector>

namespace Chess
{
    namespace Piece
    {
        class Pawn : public IPiece
        {
        public:
            Pawn(Position pos, PieceColor color, IBoard* board);
            Pawn(IPieceable* data, IAllocatable* loc);
            Pawn(const IPiece& right);

            IPiece* clone(IBoard* board) const override final;
            void getMoves(std::vector<IMove&>& vec, bool onlyAttack = false) const override final;
        };
    }
}