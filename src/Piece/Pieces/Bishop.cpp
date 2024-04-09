#include "ChessLib/Piece/Pieces/Bishop.hpp"

namespace Chess
{
    namespace Pieces
    {
        Bishop::Bishop(Position pos, PieceColor color, std::weak_ptr<Board>& board)
            :
            MovablePiece(pos, PieceType::Bishop, color, board)
        {}

        Bishop::Bishop(Piece& piece, std::weak_ptr<Board>& board)
            :
            MovablePiece(piece, board)
        {
            type = PieceType::Bishop;
        }

        Bishop::Bishop(MovablePiece& right)
            :
            MovablePiece(right)
        {
            type = PieceType::Bishop;
        }

        std::shared_ptr<MovablePiece> Bishop::clone(std::weak_ptr<Board> board) const
        {
            return std::make_shared<MovablePiece>(new Bishop((Piece)*this, board));
        }

        void Bishop::getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack) const
        {
            if (this->deleted) return;

            // X+Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x + i, pos.y + i);
                if (!move(movePos, vec)) break;
            }

            // X+Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x + i, pos.y - i);
                if (!move(movePos, vec)) break;
            }

            // X-Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x - i, pos.y + i);
                if (!move(movePos, vec)) break;
            }

            // X-Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x - i, pos.y - i);
                if (!move(movePos, vec)) break;
            }
        }

        bool Bishop::move(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const
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