#pragma once

#include "ChessLib/Move.hpp"
#include "ChessLib/Board.hpp"
#include "ChessLib/Piece/Piece.hpp"

#include <vector>
#include <memory>

namespace Chess
{
    class IMovablePiece : public IPiece
    {
    public:
        IMovablePiece(const IPiece& piece, std::weak_ptr<Board> board);

        virtual std::shared_ptr<MovablePiece> clone(std::weak_ptr<Board> board) const = 0;
        virtual void getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack = false) const = 0;

    protected:
        std::weak_ptr<Board> board;
    };

    typedef IMovablePiece MovablePiece;
}
