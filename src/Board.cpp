#include "ChessLib/Board.hpp"

namespace Chess
{
    Board::Board()
        :
        IBoard(PieceColor::Null, PieceColor::White, 0),
        boardMap(new unsigned int*[8])
    {
        for (int i = 0; i < 8; ++i)
        {
            this->boardMap[i] = new unsigned int[8];
            for (int j = 0; j < 8; ++j)
            {
                this->boardMap[i][j] = 0;
            }
        }
        setDefaultPieces();
    }

    Board::Board(const Board& right) : IBoard(right), boardMap(new unsigned int* [8])
    {
        for (int i = 0; i < 8; ++i)
        {
            this->boardMap[i] = new unsigned int[8];
            for (int j = 0; j < 8; ++j)
            {
                this->boardMap[i][j] = 0;
            }
        }

        pieces.clear();
        for (IPiece* piece : right.pieces)
        {
            if (piece == nullptr)
                pieces.push_back(piece);
            else
                pieces.push_back(piece->clone(this));
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

        for(IPiece*& piece : this->pieces)
        {
            delete piece;
            piece = nullptr;
        }
    }

    IPieceable* Board::getPiece(const Position& pos) const
    {
        return pieces.at(boardMap[pos.y][pos.x]);
    }

    std::vector<IPiece*>& Board::getPieces()
    {
        return pieces;
    }

    const std::vector<IPiece*>& Board::getPieces() const
    {
        return pieces;
    }

    std::vector<IPieceable*> Board::getPieces(PieceType type, PieceColor color) const
    {
        std::vector<IPieceable*> vec;
        for (IPieceable* piece : getPieces())
        {
            if (piece == nullptr) continue;
            if (piece->deleted) continue;
            if (color != piece->color && color != PieceColor::All) continue;
            if (type != piece->type && type != PieceType::Null) continue;
            vec.push_back(piece);
        }
        return vec;
    }

    void Board::updateMap()
    {
        clearBoardMap();
        buildBoardMap();
    }

    void Board::addPiece(IPiece* piece)
    {
        pieces.push_back(piece);
    }

    void Board::buildBoardMap()
    {
        for (unsigned int i = 1; i < pieces.size(); ++i)
        {
            IPiece* piece = pieces.at(i);
            if (piece->deleted) continue;
            int x = piece->pos.x;
            int y = piece->pos.y;
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

    void Board::clearPieces()
    {
        pieces.clear();
        pieces.push_back(nullptr);
    }

    void Board::setDefaultPieces()
    {
        clearBoardMap();
        clearPieces();

        for (int i = 0; i < 8; ++i)
        {
            addPiece(new Figures::Pawn(Position(i, 1), PieceColor::White, this));

            addPiece(new Figures::Pawn(Position(i, 6), PieceColor::Black, this));
        }

        addPiece(new Figures::Rook(Position(0, 0), PieceColor::White, this));
        addPiece(new Figures::Rook(Position(7, 0), PieceColor::White, this));
        addPiece(new Figures::Knight(Position(1, 0), PieceColor::White, this));
        addPiece(new Figures::Knight(Position(6, 0), PieceColor::White, this));
        addPiece(new Figures::Bishop(Position(2, 0), PieceColor::White, this));
        addPiece(new Figures::Bishop(Position(5, 0), PieceColor::White, this));
        addPiece(new Figures::Queen(Position(4, 0), PieceColor::White, this));
        addPiece(new Figures::King(Position(3, 0), PieceColor::White, this));

        addPiece(new Figures::Rook(Position(0, 7), PieceColor::Black, this));
        addPiece(new Figures::Rook(Position(7, 7), PieceColor::Black, this));
        addPiece(new Figures::Knight(Position(1, 7), PieceColor::Black, this));
        addPiece(new Figures::Knight(Position(6, 7), PieceColor::Black, this));
        addPiece(new Figures::Bishop(Position(2, 7), PieceColor::Black, this));
        addPiece(new Figures::Bishop(Position(5, 7), PieceColor::Black, this));
        addPiece(new Figures::Queen(Position(4, 7), PieceColor::Black, this));
        addPiece(new Figures::King(Position(3, 7), PieceColor::Black, this));

        buildBoardMap();
    }
}

