#pragma once

#include <vector>
#include "Defines.hpp"
#include "Board.hpp"
#include "ChessLib/Piece/Pieces.hpp"
#include "IMove.hpp"

namespace Chess
{
    class Game
    {
    public:
        Game(PieceType (*getNewTypeWhite)(), PieceType (*getNewTypeBlack)());
        Game(const Game& right);
        ~Game();

        const IPieceable* get(Position pos) const;
        int getResult() const;
        const Board& getBoard() const;

        Game& operator=(const Game& right);

        bool moving(Position pos1, Position pos2);

    private:
        Board* board;

        PieceType (*getNewTypeWhite)();
        PieceType (*getNewTypeBlack)();
    };
}

