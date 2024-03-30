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
                this->boardMap[i][j] = -1;
            }
        }
        reset();
    }

    Board::Board(const Board& right)
        :
        IBoard(right),
        boardMap(new unsigned int* [8])
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
            if (!boardMap[i]) continue;

            delete[] boardMap[i];
            boardMap[i] = nullptr;
        }
        delete[] boardMap;
        boardMap = nullptr;

        for(IPiece*& piece : pieces)
        {
            if (!piece) continue;

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
            if (type != piece->type && type != PieceType::All) continue;

            vec.push_back(piece);
        }
        return vec;
    }

    IMove* Board::getMove(const Position& start_pos, const Position& end_pos) const
    {
        int piece_id = boardMap[start_pos.y][start_pos.x];
        IPiece* piece = pieces[piece_id];

        std::vector<IMove*> moves;
        piece->getMoves(moves);

        for (IMove* move : moves)
        {
            try
            {
                if (move->getSteps().at(start_pos) == end_pos)
                {
                    return move;
                }
            }
            catch (std::out_of_range&) {}
        }
    
        return nullptr;
    }

    void Board::getMoves(const Position& pos, std::vector<IMove*>& vec) const
    {
        int piece_id = boardMap[pos.y][pos.x];
        IPiece* piece = pieces[piece_id];

        piece->getMoves(vec);
    }

    void Board::getMoves(std::vector<IMove*>& vec) const
    {
        for (IPiece* piece : pieces)
        {
            piece->getMoves(vec);
        }
    }

    void Board::updatePieceType(const Position& pos, PieceType new_type)
    {
        int piece_id = boardMap[pos.x][pos.y];

        if (piece_id == -1)
            throw std::logic_error("Detected a logical error");

        IPiece*& piece = pieces[piece_id];

        if (piece == nullptr)
            throw std::logic_error("Detected a logical error");

        IPiece* new_piece;

        switch (new_type)
        {
        case PieceType::Pawn:
            new_piece = new Piece::Pawn(*piece);
            break;

        case PieceType::Rook:
            new_piece = new Piece::Rook(*piece);
            break;

        case PieceType::Knight:
            new_piece = new Piece::Knight(*piece);
            break;

        case PieceType::Bishop:
            new_piece = new Piece::Bishop(*piece);
            break;

        case PieceType::Queen:
            new_piece = new Piece::Bishop(*piece);
            break;

        case PieceType::King:
            new_piece = new Piece::Bishop(*piece);
            break;

        default:
            break;
        }

        delete pieces[piece_id];
        pieces[piece_id] = new_piece;
    }

    void Board::updateMap()
    {
        clearBoardMap();
        buildBoardMap();
    }

    void Board::reset()
    {
        result = PieceColor::Null;
        moveColor = PieceColor::White;
        moveCounter = 0;

        clearBoardMap();
        clearPieces();

        for (int i = 0; i < 8; ++i)
        {
            addPiece(new Piece::Pawn(Position(i, 1), PieceColor::White, this));

            addPiece(new Piece::Pawn(Position(i, 6), PieceColor::Black, this));
        }

        addPiece(new Piece::Rook(Position(0, 0), PieceColor::White, this));
        addPiece(new Piece::Rook(Position(7, 0), PieceColor::White, this));
        addPiece(new Piece::Knight(Position(1, 0), PieceColor::White, this));
        addPiece(new Piece::Knight(Position(6, 0), PieceColor::White, this));
        addPiece(new Piece::Bishop(Position(2, 0), PieceColor::White, this));
        addPiece(new Piece::Bishop(Position(5, 0), PieceColor::White, this));
        addPiece(new Piece::Queen(Position(4, 0), PieceColor::White, this));
        addPiece(new Piece::King(Position(3, 0), PieceColor::White, this));

        addPiece(new Piece::Rook(Position(0, 7), PieceColor::Black, this));
        addPiece(new Piece::Rook(Position(7, 7), PieceColor::Black, this));
        addPiece(new Piece::Knight(Position(1, 7), PieceColor::Black, this));
        addPiece(new Piece::Knight(Position(6, 7), PieceColor::Black, this));
        addPiece(new Piece::Bishop(Position(2, 7), PieceColor::Black, this));
        addPiece(new Piece::Bishop(Position(5, 7), PieceColor::Black, this));
        addPiece(new Piece::Queen(Position(4, 7), PieceColor::Black, this));
        addPiece(new Piece::King(Position(3, 7), PieceColor::Black, this));

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
                boardMap[i][j] = -1;
            }
        }
    }

    void Board::clearPieces()
    {
        pieces.clear();
        pieces.push_back(nullptr);
    }
}

