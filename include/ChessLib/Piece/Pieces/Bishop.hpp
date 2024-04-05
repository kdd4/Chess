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
        class Bishop : public IMovablePiece
        {
        public:
            Bishop(Position pos, PieceColor color, std::weak_ptr<Board>& board);
            Bishop(Piece& piece, std::weak_ptr<Board>& board);
            Bishop(MovablePiece& right);

            std::shared_ptr<MovablePiece> clone(std::weak_ptr<Board> board) const override final;
            void getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack = false) const override final;

        private:
            bool move(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const;
        };
    }
}
