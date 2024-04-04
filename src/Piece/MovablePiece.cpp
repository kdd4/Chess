#include "ChessLib/Piece/MovablePiece.hpp"

namespace Chess
{
    IMovablePiece::IMovablePiece(const IPiece& piece, std::weak_ptr<Board> board)
        :
        IPiece(piece),
        board(board)
    {}
}
