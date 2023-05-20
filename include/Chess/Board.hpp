#pragma once

#include "Position.hpp"
#include "Defines.hpp"

#include "Figure.hpp"
#include "Figures.hpp"

#include <vector>


namespace Chess
{
    class Figure;
    struct Move;

    class Board
    {
    public:
        Board();
        Board(const Board& right);
        ~Board();

        Figure*& getFigure(const Position& pos);
        const Figure*& getFigure(const Position& pos) const;

        std::vector<Figure*>& getFigures();
        const std::vector<Figure*>& getFigures() const;

        std::vector<Move> getAllMoves(const std::vector<Figure*>& vec, bool onlyAttack = false) const;
        std::vector<Figure*> findFigures(Figures::Type type, int color) const;

        int result;
        int moveColor;
        int moveCounter;

        void update();

    private:
        void addFigure(Figure* figure);

        std::vector<Figure*> figures = {nullptr};

        unsigned int** boardMap = nullptr;
        void buildBoardMap();
        void clearBoardMap();
        void clearFigures();

        void setDefaultFigures();
    };
}

