#pragma once

#include "ChessLib/IMove.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Piece/IAllocatable.hpp"
#include "ChessLib/Piece/IPieceable.hpp"

#include <vector>

namespace Chess
{
    class IPiece : public IAllocatable, public IPieceable
    {
    public:
        IPiece(IPieceable& pieceable, IAllocatable& allocatable);
        IPiece(const IPiece& right);

        virtual IPiece* clone(IBoard* board) const = 0;
        virtual void getMoves(std::vector<IMove&>& vec, bool onlyAttack = false) const = 0;
    };
}