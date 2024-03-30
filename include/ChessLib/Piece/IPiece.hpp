#pragma once

#include "ChessLib/IMove.hpp"
#include "ChessLib/IBoard.hpp"

#include "ChessLib/Piece/IPieceable.hpp"

#include <vector>
#include <memory>

namespace Chess
{
    class IPiece : public IPieceable
    {
    public:
        IPiece(const IPieceable& pieceable, IBoard* const board);
        IPiece(const IPiece& right);

        virtual IPiece* clone(IBoard* board) const = 0;
        virtual void getMoves(std::vector<IMove*>& vec, bool onlyAttack = false) const = 0;

    protected:
        IBoard* board;
    };
}
