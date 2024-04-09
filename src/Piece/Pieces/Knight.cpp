#include "ChessLib/Piece/Pieces/Knight.hpp"

namespace Chess
{
    namespace Pieces
    {
        Knight::Knight(Position pos, PieceColor color, std::weak_ptr<Board>& board)
            :
            MovablePiece(pos, PieceType::Knight, color, board)
        {}

        Knight::Knight(Piece& piece, std::weak_ptr<Board>& board)
            :
            MovablePiece(piece, board)
        {
            type = PieceType::Knight;
        }

        Knight::Knight(MovablePiece& right)
            :
            MovablePiece(right)
        {
            type = PieceType::Knight;
        }

        std::shared_ptr<MovablePiece> Knight::clone(std::weak_ptr<Board> board) const
        {
            return std::make_shared<MovablePiece>(new Knight((Piece)*this, board));
        }

        void Knight::getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack) const
        {
            if (this->deleted) return;

            move({ pos.x + 1, pos.y + 2 }, vec);
            move({ pos.x + 1, pos.y - 2 }, vec);
            move({ pos.x - 1, pos.y + 2 }, vec);
            move({ pos.x - 1, pos.y - 2 }, vec);

            move({ pos.x + 2, pos.y + 1 }, vec);
            move({ pos.x + 2, pos.y - 1 }, vec);
            move({ pos.x - 2, pos.y + 1 }, vec);
            move({ pos.x - 2, pos.y - 1 }, vec);
        }

        bool Knight::move(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const
        {
            if (!pos.check()) return false;

            std::shared_ptr<Piece> attackedPiece = board.lock()->getPiece(pos);

            if (attackedPiece != nullptr)
            {
                if (attackedPiece->color == color)
                    return false;
            }

            std::shared_ptr<ImplMove> move(new ImplMove(board));

            move->appendAttack(pos);
            move->appendStep(this->pos, pos);
            vec.push_back(move);

            return attackedPiece == nullptr;
        }

    }
}