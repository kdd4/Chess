#include "Chess/Board.hpp"

namespace Chess
{
    Board::Board() : result(Color::Null), moveColor(Color::White), moveCounter(0), boardMap(new unsigned int*[8])
    {
        for (int i = 0; i < 8; ++i)
        {
            this->boardMap[i] = new unsigned int[8];
            for (int j = 0; j < 8; ++j)
            {
                this->boardMap[i][j] = 0;
            }
        }
        setDefaultFigures();
    }

    Board::Board(const Board& right) : result(right.result), moveColor(right.moveColor), moveCounter(right.moveCounter), boardMap(new unsigned int*[8])
    {
        for (int i = 0; i < 8; ++i)
        {
            this->boardMap[i] = new unsigned int[8];
            for (int j = 0; j < 8; ++j)
            {
                this->boardMap[i][j] = 0;
            }
        }

        figures.clear();
        for (Figure* figure : right.figures)
        {
            if (figure == nullptr)
                figures.push_back(figure);
            else
                figures.push_back(figure->clone(this));
        }
        buildBoardMap();
    }

    Board::~Board()
    {
        for (int i = 0; i < 8; ++i)
        {
            delete[] this->boardMap[i];
            boardMap[i] = nullptr;
        }
        delete[] this->boardMap;

        for(Figure*& fig : this->figures)
        {
            delete fig;
            fig = nullptr;
        }
    }

    Figure*& Board::getFigure(const Position& pos)
    {
        return figures.at(boardMap[pos.y][pos.x]);
    }

    const Figure*& Board::getFigure(const Position& pos) const
    {
        return const_cast<const Figure*&>(figures.at(boardMap[pos.y][pos.x]));
    }

    std::vector<Figure*>& Board::getFigures()
    {
        return figures;
    }

    const std::vector<Figure*>& Board::getFigures() const
    {
        return figures;
    }

    std::vector<Move> Board::getAllMoves(const std::vector<Figure*>& vec, bool onlyAttack) const
    {
        std::vector<Move> moves;
        for (Figure* figure : vec)
        {
            if (figure == nullptr) continue;
            if (figure->deleted) continue;
            figure->getMoves(moves, onlyAttack);
        }
        return moves;
    }

    std::vector<Figure*> Board::findFigures(Figures::Type type, int color) const
    {
        std::vector<Figure*> vec;
        for (Figure* figure : getFigures())
        {
            if (figure == nullptr) continue;
            if (figure->deleted) continue;
            if (color != figure->color && color != Color::Both) continue;
            if (type != figure->type && type != Figures::Type::Null) continue;
            vec.push_back(figure);
        }
        return vec;
    }

    void Board::update()
    {
        clearBoardMap();
        buildBoardMap();
    }

    void Board::addFigure(Figure* figure)
    {
        figures.push_back(figure);
    }

    void Board::buildBoardMap()
    {
        for (unsigned int i = 1; i < figures.size(); ++i)
        {
            Figure* figure = figures.at(i);
            if (figure->deleted) continue;
            int x = figure->pos.x;
            int y = figure->pos.y;
            this->boardMap[y][x] = i;
        }
    }

    void Board::clearBoardMap()
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                boardMap[i][j] = 0;
            }
        }
    }

    void Board::clearFigures()
    {
        figures.clear();
        figures.push_back(nullptr);
    }

    void Board::setDefaultFigures()
    {
        clearBoardMap();
        clearFigures();

        for (int i = 0; i < 8; ++i)
        {
            addFigure(new Figures::Pawn(Position(i, 1), Color::White, this));

            addFigure(new Figures::Pawn(Position(i, 6), Color::Black, this));
        }

        addFigure(new Figures::Rook(Position(0, 0), Color::White, this));
        addFigure(new Figures::Rook(Position(7, 0), Color::White, this));
        addFigure(new Figures::Knight(Position(1, 0), Color::White, this));
        addFigure(new Figures::Knight(Position(6, 0), Color::White, this));
        addFigure(new Figures::Bishop(Position(2, 0), Color::White, this));
        addFigure(new Figures::Bishop(Position(5, 0), Color::White, this));
        addFigure(new Figures::Queen(Position(4, 0), Color::White, this));
        addFigure(new Figures::King(Position(3, 0), Color::White, this));

        addFigure(new Figures::Rook(Position(0, 7), Color::Black, this));
        addFigure(new Figures::Rook(Position(7, 7), Color::Black, this));
        addFigure(new Figures::Knight(Position(1, 7), Color::Black, this));
        addFigure(new Figures::Knight(Position(6, 7), Color::Black, this));
        addFigure(new Figures::Bishop(Position(2, 7), Color::Black, this));
        addFigure(new Figures::Bishop(Position(5, 7), Color::Black, this));
        addFigure(new Figures::Queen(Position(4, 7), Color::Black, this));
        addFigure(new Figures::King(Position(3, 7), Color::Black, this));

        buildBoardMap();
    }
}

