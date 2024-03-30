#include "ChessLib/Piece/IPiece.hpp"

namespace Chess
{
    IPiece::IPiece(const IPieceable& pieceable, IBoard* const board)
        :
        IPieceable(pieceable),
        board(board)
    {}

    IPiece::IPiece(const IPiece& right)
        :
        IPieceable(right),
        board(right.board)
    {}
}
