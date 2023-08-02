#pragma once

#include "ChessLib/IMove.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Piece/Allocatable.hpp"
#include "ChessLib/Piece/Pieceable.hpp"

namespace Chess
{
    class IPiece : public Allocatable, public Pieceable
    {
    public:
        virtual IPiece* clone(IBoard* board) const = 0;
        virtual void getMoves(std::vector<IMove>& vec, bool onlyAttack = false) const = 0;
    };
}
