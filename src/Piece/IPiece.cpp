#include "ChessLib/Piece/IPiece.hpp"

namespace Chess
{
    IPiece::IPiece(IPieceable& pieceable, IAllocatable& allocatable)
        :
        IPieceable(pieceable),
        IAllocatable(allocatable)
    {}

    IPiece::IPiece(const IPiece& right)
        :
        IPieceable(right),
        IAllocatable(right)
    {}
}
