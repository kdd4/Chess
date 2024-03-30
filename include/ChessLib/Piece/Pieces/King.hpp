#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Move.hpp"

#include <vector>

namespace Chess
{
    namespace Piece
    {
        class King : public IPiece
        {
        public:
            King(Position pos, PieceColor color, IBoard* board);
            King(IPieceable* data, IAllocatable* loc);
            King(const IPiece& right);

            IPiece* clone(IBoard* board) const override final;
            void getMoves(std::vector<IMove*>& vec, bool onlyAttack = false) const override final;

            void QueensideCastling(std::vector<Move*>& vec) const;
            void KingsideCastling(std::vector<Move*>& vec) const;
        };
    }
}
