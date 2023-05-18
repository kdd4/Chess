#pragma once

#include <vector>
#include "Defines.hpp"
#include "Board.hpp"

namespace Chess
{
    class Figure
    {
    public:
        Figure(Position position, int color, Figures::Type type, Chess::Board* board, int moveCount, int lastMoveMoment, bool deleted);
        virtual ~Figure();
        virtual Figure* clone(Board* board) const = 0;
        virtual void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const = 0;

        Position pos;
        int color = Color::Null;
        int lastMoveMoment = -1;
        int moveCount = 0;
        bool deleted = false;
        Board* board;
        Figures::Type type;
    };

    namespace Figures
    {
        class Pawn : public Figure
        {
        public:
            Pawn(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Rook : public Figure
        {
        public:
            Rook(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Knight : public Figure
        {
        public:
            Knight(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Bishop : public Figure
        {
        public:
            Bishop(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class Queen : public Figure
        {
        public:
            Queen(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;
        };

        class King : public Figure
        {
        public:
            King(Position position, int color, Board* board, int moveCount = 0, int lastMoveMoment = -1, bool deleted = false);
            Figure* clone(Board* board) const override final;
            void getMoves(std::vector<Move>& vec, bool onlyAttack = false) const override final;

            bool LeftCastling() const;
            bool RightCastling() const;
        };
    }
}

