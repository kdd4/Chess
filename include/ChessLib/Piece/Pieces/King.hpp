#pragma once

#include "ChessLib/Piece/MovablePiece.hpp"
#include "ChessLib/Board.hpp"

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"
#include "ChessLib/ImplMove.hpp"

#include <vector>
#include <memory>

namespace Chess
{
    namespace Pieces
    {
        class King : public IMovablePiece
        {
        public:
            King(Position pos, PieceColor color, std::weak_ptr<Board>& board);
            King(Piece& piece, std::weak_ptr<Board>& board);
            King(MovablePiece& right);

            std::shared_ptr<MovablePiece> clone(std::weak_ptr<Board> board) const override final;
            void getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack = false) const override final;

        private:
            void King::QueensideCastling(std::vector<std::shared_ptr<Move>>& vec) const;
            void King::KingsideCastling(std::vector<std::shared_ptr<Move>>& vec) const
        };
    }
}
