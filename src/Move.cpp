#include "ChessLib/Move.hpp"

namespace Chess
{
	Move::Move() {}

    Move::Move(Position start_pos, Position end_pos)
    {

    }

    Move::Move(Position start_pos, Position end_pos, Position attacked_pos)
    {

    }

    void Move::make(IBoard* board) override
    {

    }

    void Move::cancel(IBoard* board) override
    {

    }

    void Move::appendStep(Position old_pos, Position new_pos)
    {

    }

    void Move::appendAttack(Position attacked_pos)
    {

    }

    void Move::updateType(Position old_pos, PieceType old_type, PieceType new_type)
    {

    }
}
