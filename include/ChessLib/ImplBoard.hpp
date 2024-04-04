#pragma once

#include <vector>
#include <stdexcept>
#include <memory>

#include "ChessLib/Piece/Pieces.hpp"

#include "ChessLib/Board.hpp"
#include "ChessLib/Piece/MovablePiece.hpp"
#include "ChessLib/Piece/Piece.hpp"
#include "ChessLib/Move.hpp"

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

namespace Chess
{
    class ImplBoard : public IBoard
    {
    public:
        ImplBoard();
        ImplBoard(const ImplBoard& right);

        std::shared_ptr<MovablePiece> getMovablePiece(const Position& pos) const;

        std::shared_ptr<Piece> getPiece(const Position& pos) const override;
        std::vector<std::shared_ptr<Piece>> getPieces(PieceType type, PieceColor color) const override;

        std::shared_ptr<Move> getMove(const Position& start_pos, const Position& end_pos) const override;
        void getMoves(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const override;
        void getMoves(std::vector<std::shared_ptr<Move>>& vec) const override;

        PieceColor getResult() const override;
        PieceColor getMoveColor() const override;

    private:
        void reset();
        void addPiece(MovablePiece* piece);

        std::vector<std::shared_ptr<MovablePiece>> pieces;

        PieceColor result;
        PieceColor moveColor;
        int moveCounter;
    };
}

