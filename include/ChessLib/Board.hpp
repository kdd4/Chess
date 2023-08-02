#pragma once

#include "Piece/Type.hpp"
#include "Position.hpp"

#include "Piece/Pieces.hpp"

#include "Piece/IPiece.hpp"
#include "IMove.hpp"

#include <vector>

namespace Chess
{
    class Board
    {
    public:
        Board();
        Board(const Board& right);
        ~Board();

        IPiece*& getFigure(const Position& pos);
        const IPiece*& getFigure(const Position& pos) const;

        std::vector<IPiece*>& getFigures();
        const std::vector<IPiece*>& getFigures() const;

        std::vector<Move> getAllMoves(const std::vector<IPiece*>& vec, bool onlyAttack = false) const;  // вынести их
        std::vector<IPiece*> findFigures(PieceType type, PieceColor color) const;

        int result;
        int moveColor;
        int moveCounter;

        void update();

    private:
        void addFigure(IPiece* figure);

        std::vector<IPiece*> figures = {nullptr};

        unsigned int** boardMap = nullptr;
        void buildBoardMap();
        void clearBoardMap();
        void clearFigures();

        void setDefaultFigures();
    };
}

