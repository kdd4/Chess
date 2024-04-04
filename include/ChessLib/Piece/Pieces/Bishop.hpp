#pragma once

#include "ChessLib/Piece/MovablePiece.hpp"
#include "ChessLib/Board.hpp"

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"
#include "ChessLib/Move.hpp"

#include <vector>

namespace Chess
{
    namespace Pieces
    {
        class Bishop : public IMovablePiece
        {
        public:
            Bishop(Position pos, PieceColor color, Board board);
            Bishop(Piece data, Board board);
            Bishop(const MovablePiece right);

            MovablePiece clone(Board board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };
    }
}
