#include "ChessLib/Move.hpp"

namespace Chess
{
    ImplMove::ImplMove(IBoard* board)
        : 
        board(board)
    {}

    ImplMove::ImplMove(IBoard* board, Position start_pos, Position end_pos)
    {

    }

    ImplMove::ImplMove(IBoard* board, Position start_pos, Position end_pos, Position attacked_pos)
    {

    }

    void ImplMove::make()
    {

    }

    void ImplMove::cancel()
    {

    }

    void ImplMove::appendStep(Position old_pos, Position new_pos)
    {

    }

    void ImplMove::appendAttack(Position attacked_pos)
    {

    }

    void ImplMove::updateType(Position old_pos, PieceType old_type, PieceType new_type)
    {

    }
}
