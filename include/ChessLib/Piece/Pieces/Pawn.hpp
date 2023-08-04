#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Move.hpp"

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
            void getMoves(std::vector<Move*>& vec, bool onlyAttack = false) const override final;

        private:
            Move* moveGenerator(Position start_pos, Position end_pos);
            Move* moveGenerator(Position start_pos, Position end_pos, Position attacked_pos);
        };
    }
}
