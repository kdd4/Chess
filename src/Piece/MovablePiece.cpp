#include "ChessLib/Piece/MovablePiece.hpp"

namespace Chess
{
    IMovablePiece::IMovablePiece(Position pos, PieceType type, PieceColor color, std::weak_ptr<Board> board, std::vector<int> moveMoment, bool deleted)
        :
        IPiece(pos, type, color, moveMoment, deleted),
        board(board)
    {}

    IMovablePiece::IMovablePiece(const IPiece& piece, const std::weak_ptr<Board>& board)
        :
        IPiece(piece),
        board(board)
    {}

    IMovablePiece::IMovablePiece(const std::shared_ptr<IMovablePiece>& right)
        :
        IPiece(*right),
        board(right->board)
    {}
}
