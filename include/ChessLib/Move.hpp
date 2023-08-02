#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"
#include "ChessLib/IBoard.hpp"
#include "ChessLib/IMove.hpp"

#include <map>
#include <set>

namespace Chess
{
    class Move : public IMove
    {
    public:
        Move();

        void make(IBoard* board) override;
        void cancel(IBoard* board) override;

        void appendStep(Position old_pos, Position new_pos);
        void appendAttack(Position attacked_pos);
        void updateType(Position pos, PieceType old_type, PieceType new_type);

    private:
        std::map<Position, Position> steps;
        std::set<Position> attackedPositions;
        std::map<Position, std::pair<PieceType, PieceType>> updateType;
    };
}
