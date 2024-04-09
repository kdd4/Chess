#include "ChessLib/Piece/Pieces/Pawn.hpp"

namespace Chess
{
    namespace Pieces
    {
        Pawn::Pawn(Position pos, PieceColor color, std::weak_ptr<Board>& board)
            :
            MovablePiece(pos, PieceType::Pawn, color, board)
        {}

        Pawn::Pawn(Piece& piece, std::weak_ptr<Board>& board)
            :
            MovablePiece(piece, board)
        {
            type = PieceType::Pawn;
        }

        Pawn::Pawn(MovablePiece& right)
            :
            MovablePiece(right)
        {
            type = PieceType::Pawn;
        }

        std::shared_ptr<MovablePiece> Pawn::clone(std::weak_ptr<Board> board) const
        {
            return std::make_shared<MovablePiece>(new Pawn((Piece)*this, board));
        }

        void Pawn::getMoves(std::vector<std::shared_ptr<Move>>& vec, bool onlyAttack) const
        {
            if (this->deleted) return;

            std::shared_ptr<ImplMove> move;
            std::shared_ptr<Piece> attacked_place, move_place;
            Position move_step;

            move_step = Position(pos.x, pos.y + getDirection());
            if (!onlyAttack && move_step.check())
            {
                move_place = board.lock()->getPiece(move_step);
                if (move_place == nullptr)
                {
                    move = std::make_shared<ImplMove>(new ImplMove(board));
                    move->appendStep(this->pos, move_step);

                    if (move_step.y == 7)
                    {
                        move->changeType(pos, type, PieceType::Queen); // CHANGE IT
                    }
                    vec.push_back(move);

                    move_step = Position(pos.x, pos.y + getDirection() * 2);
                    if (this->getLastMoveMoment() == -1 && move_step.check())
                    {
                        attacked_place = board.lock()->getPiece(move_step);
                        if (attacked_place == nullptr)
                        {
                            move = std::make_shared<ImplMove>(new ImplMove(board));
                            move->appendStep(this->pos, move_step);
                            vec.push_back(move);
                        }
                    }
                }
            }

            move_step = Position(pos.x + 1, pos.y + getDirection());
            if (move_step.check())
            {
                attacked_place = board.lock()->getPiece(move_step);
                if (attacked_place != nullptr)
                {
                    if (attacked_place->color != color)
                    {
                        move = std::make_shared<ImplMove>(new ImplMove(board));
                        move->appendStep(this->pos, move_step);
                        move->appendAttack(move_step);
                        vec.push_back(move);
                    }
                }
                else // attacked_place == nullptr
                {
                    attacked_place = board.lock()->getPiece(Position(pos.x + 1, pos.y));
                    if (attacked_place != nullptr)
                    {
                        if (attacked_place->color != color && attacked_place->type == PieceType::Pawn)
                        {
                            if (attacked_place->getLastMoveMoment() == board.lock()->getMoveCount() - 1 \
                                && attacked_place->getMoveCount() == 1)
                            {
                                move = std::make_shared<ImplMove>(new ImplMove(board));
                                move->appendStep(this->pos, move_step);
                                move->appendAttack(Position(pos.x + 1, pos.y));
                                vec.push_back(move);
                            }
                        }
                    }
                }
            }

            move_step = Position(pos.x - 1, pos.y + getDirection());
            if (move_step.check())
            {
                attacked_place = board.lock()->getPiece(move_step);
                if (attacked_place != nullptr)
                {
                    if (attacked_place->color != color)
                    {
                        move = std::make_shared<ImplMove>(new ImplMove(board));
                        move->appendStep(this->pos, move_step);
                        move->appendAttack(move_step);
                        vec.push_back(move);
                    }
                }
                else // attacked_place == nullptr
                {
                    attacked_place = board.lock()->getPiece(Position(pos.x - 1, pos.y));
                    if (attacked_place != nullptr)
                    {
                        if (attacked_place->color != color && attacked_place->type == PieceType::Pawn)
                        {
                            if (attacked_place->getLastMoveMoment() == board.lock()->getMoveCount() - 1 \
                                && attacked_place->getMoveCount() == 1)
                            {
                                move = std::make_shared<ImplMove>(new ImplMove(board));
                                move->appendStep(this->pos, move_step);
                                move->appendAttack(Position(pos.x - 1, pos.y));
                                vec.push_back(move);
                            }
                        }
                    }
                }
            }
        }

    }
}
