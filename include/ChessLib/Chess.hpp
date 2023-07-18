#pragma once

#include <vector>
#include "Defines.hpp"
#include "Board.hpp"
#include "Figures.hpp"
#include "Move.hpp"

namespace Chess
{
    class Game
    {
    public:
        Game(Figures::Type (*getNewTypeWhite)(), Figures::Type (*getNewTypeBlack)());
        Game(const Game& right);
        ~Game();

        const Figure* get(Position pos) const;
        int getResult() const;
        const Board& getBoard() const;

        Game& operator=(const Game& right);

        bool moving(Position pos1, Position pos2);

    private:
        Board* board;

        Figures::Type (*getNewTypeWhite)();
        Figures::Type (*getNewTypeBlack)();

        void makeMove(Move& moving);
        void cancelMove(Move& moving);

        // Checking the possibility of making a move without changing the board
        bool checkMove(Figure* movingFigure, Move& moving);

        void updateFigure(Figure*& figure, Figures::Type newType);
    };
}

