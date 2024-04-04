#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"
#include "ChessLib/Board.hpp"
#include "ChessLib/Move.hpp"

#include <map>
#include <set>

namespace Chess
{
    class ImplMove : public IMove
    {
    public:
        ImplMove(std::weak_ptr<Board> board);

        void make() override;
        void cancel() override;

        const std::map<Position, Position>& getSteps() const override;
        const std::set<Position>& getAttackedPositions() const override;
        const std::map<Position, PieceType>& getTypeChanges() const override;

        void appendStep(Position old_pos, Position new_pos);
        void appendAttack(Position attacked_pos);
        void updateType(Position old_pos, PieceType old_type, PieceType new_type);

    private:
        std::weak_ptr<Board> board;
        //int move_cnt; add hash

        std::map<Position, Position> steps;
        std::set<Position> attackedPositions;
        std::map<Position, PieceType> updateType;
    };
}
