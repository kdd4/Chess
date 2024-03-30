#pragma once

#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Move.hpp"

#include <vector>

namespace Chess
{
    namespace Piece
    {
        class Bishop : public IPiece
        {
        public:
            Bishop(Position pos, PieceColor color, IBoard* board);
            Bishop(IPieceable* data, IBoard* const board);
            Bishop(const IPiece& right);

            IPiece* clone(IBoard* board) const override final;
            void getMoves(std::vector<IMove*>& vec, bool onlyAttack = false) const override final;
        };
    }
}
