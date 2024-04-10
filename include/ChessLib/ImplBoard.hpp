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

        int getPieceId(const Position& pos, int moveMoment = -1, bool deleted = false) const;
        std::shared_ptr<MovablePiece> getMovablePiece(const Position& pos, int moveMoment = -1, bool deleted = false) const;
        void getAttackMoves(std::vector<std::shared_ptr<Move>>& vec, const PieceColor color = PieceColor::All) const;

        std::shared_ptr<Piece> getPiece(const Position& pos) const override;
        std::vector<std::shared_ptr<Piece>> getPieces(PieceType type = PieceType::All, PieceColor color = PieceColor::All) const override;

        std::shared_ptr<Move> getMove(const Position& start_pos, const Position& end_pos) const override;
        void getMoves(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const override;
        void getMoves(std::vector<std::shared_ptr<Move>>& vec, const PieceColor color = PieceColor::All) const override;

        PieceColor getMoveColor() const override;
        int getMoveCount() const override;

        void makeMove(const std::shared_ptr<Move> move) override;
        void cancelMove(const std::shared_ptr<Move> move) override;

    private:
        void addPiece(MovablePiece* piece);
        void changeType(const Position& pos, const PieceType type);

        std::vector<std::shared_ptr<MovablePiece>> Pieces;

        int MoveCounter;
    };
}

