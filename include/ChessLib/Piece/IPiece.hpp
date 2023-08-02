#pragma once

#include "ChessLib/IMove.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Piece/IAllocatable.hpp"
#include "ChessLib/Piece/IPieceable.hpp"

namespace Chess
{
    class IPiece : public IAllocatable, public IPieceable
    {
    public:
        virtual IPiece* clone(IBoard* board) const = 0;
        virtual void getMoves(std::vector<IMove>& vec, bool onlyAttack = false) const = 0;
    };
}