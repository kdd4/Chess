#include "ChessLib/Piece/Pieces/Queen.hpp"

namespace Chess
{
    namespace Pieces
    {
        Queen::Queen(Position pos, PieceColor color, std::weak_ptr<Board>& board)
            :
            MovablePiece(pos, PieceType::Queen, color, board)
        {}

        Queen::Queen(const Piece& piece, std::weak_ptr<Board> board)
            :
            MovablePiece(piece, board)
        {
            type = PieceType::Queen;
        }

        Queen::Queen(const MovablePiece& right)
            :
            MovablePiece(right)
        {
            type = PieceType::Queen;
        }

        std::shared_ptr<MovablePiece> Queen::clone(std::weak_ptr<Board> board) const
        {
            std::shared_ptr<MovablePiece> copy(new Queen(*this, board));
            return copy;
        }

        void Queen::getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack) const
        {
            if (this->deleted) return;

            // X+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x + i, pos.y);
                if (!move(movePos, vec)) break;
            }

            // X-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x - i, pos.y);
                if (!move(movePos, vec)) break;
            }

            // Y+
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x, pos.y + i);
                if (!move(movePos, vec)) break;
            }

            // Y-
            for (int i = 1; i < 8; ++i)
            {
                Position movePos(pos.x, pos.y - i);
                if (!move(movePos, vec)) break;
            }

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

        bool Queen::move(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const
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