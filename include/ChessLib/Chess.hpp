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

        const std::shared_ptr<Piece> get(Position pos) const;
        PieceColor getResult() const;
        const std::shared_ptr<Board> getBoard() const;

        Chess& operator=(const Chess& right);

        bool moving(Position pos1, Position pos2);

    private:
        std::shared_ptr<ImplBoard> board;
        PieceColor result;

        PieceType (*getNewTypeWhite)();
        PieceType (*getNewTypeBlack)();

        bool checkMove(std::shared_ptr<Move> move);
    };
}

