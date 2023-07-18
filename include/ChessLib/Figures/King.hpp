#pragma once

#include "ChessLib/Figure.hpp"
#include "ChessLib/Board.hpp"
#include "ChessLib/Move.hpp"

namespace Chess
{
    namespace Figures
    {
        class King : public Figure
        {
        public:
            King(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, int prevLastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;

            void QueensideCastling(std::vector<Move>& vec) const;
            void KingsideCastling(std::vector<Move>& vec) const;
        };
    }
}