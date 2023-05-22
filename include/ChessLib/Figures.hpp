#pragma once

#include "Position.hpp"
#include "Defines.hpp"

#include "Figure.hpp"
#include "Board.hpp"
#include "Move.hpp"

#include <vector>


namespace Chess
{
    class Figure;

    namespace Figures
    {
        class Pawn : public Figure
        {
        public:
            Pawn(Position position, int color, Board* board, int moveCount=0, int lastMoveMoment=-1, int prevLastMoveMoment=-1, bool deleted=false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Rook : public Figure
        {
        public:
            Rook(Position position, int color, Board* board, int moveCount=0, int lastMoveMoment=-1, int prevLastMoveMoment=-1, bool deleted=false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Knight : public Figure
        {
        public:
            Knight(Position position, int color, Board* board, int moveCount=0, int lastMoveMoment=-1, int prevLastMoveMoment=-1, bool deleted=false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Bishop : public Figure
        {
        public:
            Bishop(Position position, int color, Board* board, int moveCount=0, int lastMoveMoment=-1, int prevLastMoveMoment=-1, bool deleted=false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Queen : public Figure
        {
        public:
            Queen(Position position, int color, Board* board, int moveCount=0, int lastMoveMoment=-1, int prevLastMoveMoment=-1, bool deleted=false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class King : public Figure
        {
        public:
            King(Position position, int color, Board* board, int moveCount=0, int lastMoveMoment=-1, int prevLastMoveMoment=-1, bool deleted=false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;

            void LeftCastling(std::vector<Move>& vec) const;
            void RightCastling(std::vector<Move>& vec) const;
        };
    }
}

