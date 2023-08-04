#pragma once

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

#include "ChessLib/Piece/Pieces.hpp"

#include "ChessLib/IBoard.hpp"
#include "ChessLib/Piece/IPiece.hpp"
#include "ChessLib/Piece/IPieceable.hpp"
#include "ChessLib/IMove.hpp"

#include "Defines.hpp"

#include <vector>

namespace Chess
{
    class Board : public IBoard
    {
    public:
        Board();
        Board(const Board& right);
        ~Board();

        std::vector<IPiece*>& getPieces();
        const std::vector<IPiece*>& getPieces() const;

        IPieceable* getPiece(const Position& pos) const override;
        std::vector<IPieceable*> getPieces(PieceType type, PieceColor color) const override;

        void updatePieceType(const Position& pos, PieceType new_type) override;
        void updateMap() override;
        void reset() override;

    private:
        void addPiece(IPiece* piece);

        std::vector<IPiece*> pieces = {nullptr};

        unsigned int** boardMap = nullptr;
        void buildBoardMap();
        void clearBoardMap();
        void clearPieces();
    };
}

