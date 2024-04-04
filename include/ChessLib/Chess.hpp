#pragma once

#include <vector>

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/ImplBoard.hpp"
#include "ChessLib/Piece/Pieces.hpp"
#include "ChessLib/Move.hpp"

namespace Chess
{
    class Chess
    {
    public:
        Chess(PieceType (*getNewTypeWhite)(), PieceType (*getNewTypeBlack)());
        Chess(const Chess& right);
        ~Chess();

        const Piece get(Position pos) const;
        PieceColor getResult() const;
        const Board& getBoard() const;

        Chess& operator=(const Chess& right);

        bool moving(Position pos1, Position pos2);

    private:
        Board* board;

        PieceType (*getNewTypeWhite)();
        PieceType (*getNewTypeBlack)();
    };
}

