#include "ChessLib/Piece/Pieces/Pawn.hpp"

namespace Chess
{
    namespace Piece
    {
        Pawn::Pawn(Position pos, PieceColor color, IBoard* board)
            :
            IPiece(IPieceable(pos, PieceType::Pawn, color), IAllocatable(board))
        {}

        Pawn::Pawn(IPieceable* pieceable, IAllocatable* allocatable)
            :
            IPiece(*pieceable, *allocatable)
        {
            type = PieceType::Pawn;
        }

        Pawn::Pawn(const IPiece& right)
            :
            IPiece(right)
        {
            type = PieceType::Pawn;
        }

        IPiece* Pawn::clone(IBoard* board) const
        {
            return new Pawn(*this);
        }

        void Pawn::getMoves(std::vector<IMove&>& vec, bool onlyAttack) const
        {
            if (deleted) return;
            if (pos.y + getDirection() >= 8 || pos.y + getDirection() < 0) return;

            Position movePos = Position(pos.x, pos.y + getDirection());
            IPieceable* piece = board->getPiece(movePos);
            if (piece == nullptr && !onlyAttack)
            {
                vec.push_back(Move(pos, movePos));
                movePos = Position(pos.x, pos.y + getDirection() * 2);
                if (this->getLastMoveMoment() == -1 && movePos.check())
                {
                    piece = board->getPiece(movePos);
                    if (piece == nullptr)
                    {
                        vec.push_back(Move(pos, movePos));
                    }
                }
            }

            if (pos.x != 7)
            {
                movePos = Position(pos.x + 1, pos.y + getDirection());
                piece = board->getPiece(movePos);
                if (piece != nullptr)
                {
                    if (piece->color != color)
                    {
                        vec.push_back(Move(pos, movePos, movePos));
                    }
                }
                else
                {
                    piece = board->getPiece(Position(pos.x + 1, pos.y));
                    if (piece != nullptr)
                    {
                        if (piece->color != color && piece->type == PieceType::Pawn)
                        {
                            if (piece->getMoveCount() == 1 && piece->getLastMoveMoment() == board->moveCounter - 1)
                                vec.push_back(Move(pos, Position(pos.x + 1, pos.y + getDirection()), Position(pos.x + 1, pos.y)));
                        }
                    }
                }
            }

            if (pos.x != 0)
            {
                movePos = Position(pos.x - 1, pos.y + getDirection());
                piece = board->getPiece(movePos);
                if (piece != nullptr)
                {
                    if (piece->color != color)
                    {
                        vec.push_back(Move(pos, movePos, movePos));
                    }
                }
                else
                {
                    piece = board->getPiece(Position(pos.x - 1, pos.y));
                    if (piece != nullptr)
                    {
                        if (piece->color != color && piece->type == PieceType::Pawn)
                        {
                            if (piece->getMoveCount() == 1 && piece->getLastMoveMoment() == board->moveCounter - 1)
                                vec.push_back(Move(pos, Position(pos.x - 1, pos.y + getDirection()), Position(pos.x - 1, pos.y)));
                        }
                    }
                }
            }
        }

    }
}