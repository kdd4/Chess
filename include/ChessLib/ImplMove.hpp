#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"
#include "ChessLib/Board.hpp"
#include "ChessLib/Move.hpp"
#include "ChessLib/Piece/Piece.hpp"

#include <stdexcept>
#include <map>
#include <set>

namespace Chess
{
    class ImplMove : public IMove
    {
    public:
        ImplMove(std::weak_ptr<Board> board);

        const std::map<Position, Position>& getSteps() const override;
        const std::set<Position>& getAttackedPositions() const override;
        const std::map<Position, std::pair<PieceType, PieceType>>& getTypeChanges() const override;

        int getMoveCount() const override;

        void appendStep(Position old_pos, Position new_pos);
        void appendAttack(Position attacked_pos);
        void changeType(Position cur_pos, PieceType old_type, PieceType new_type);

    private:
        std::weak_ptr<Board> board;
        int moveCnt;

        std::map<Position, Position> steps;
        std::set<Position> attacked_positions;
        std::map<Position, std::pair<PieceType, PieceType>> type_changes;
    };
}
