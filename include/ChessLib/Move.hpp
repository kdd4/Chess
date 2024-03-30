#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"
#include "ChessLib/IBoard.hpp"
#include "ChessLib/IMove.hpp"

#include <map>
#include <set>

namespace Chess
{
    class ImplMove : public IMove
    {
    public:
        ImplMove(IBoard* board);

        void make() override;
        void cancel() override;

        const std::map<Position, Position>& getSteps() const override;
        const std::set<Position>& getAttackedPositions() const override;
        const std::map<Position, PieceType>& getTypeChanges() const override;

        void appendStep(Position old_pos, Position new_pos);
        void appendAttack(Position attacked_pos);
        void updateType(Position old_pos, PieceType old_type, PieceType new_type);

    private:
        IBoard* board;
        //int move_cnt; add hash

        std::map<Position, Position> steps;
        std::set<Position> attackedPositions;
        std::map<Position, PieceType> updateType;
    };

    class MoveFabric
    {

    };
}
