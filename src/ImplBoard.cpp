#include "ChessLib/ImplBoard.hpp"

namespace Chess
{
    ImplBoard::ImplBoard() :
        result(PieceColor::Null),
        moveColor(PieceColor::Null),
        moveCounter(-1)
    {
        reset();
    }

    ImplBoard::ImplBoard(const ImplBoard& right)
        :
        result(right.result),
        moveColor(right.moveColor),
        moveCounter(right.moveCounter)
    {
        for (std::shared_ptr<MovablePiece> piece : right.pieces)
        {
            pieces.push_back(piece->clone(std::make_shared<Board>(this)));
        }
    }

    std::shared_ptr<Piece> ImplBoard::getPiece(const Position& pos) const
    {
        return getMovablePiece(pos);
    }

    std::vector<std::shared_ptr<Piece>> ImplBoard::getPieces(PieceType type, PieceColor color) const
    {
        std::vector<std::shared_ptr<Piece>> vec;
        for (std::shared_ptr<Piece> piece : pieces)
        {
            //if (piece == nullptr) continue;
            if (piece->deleted) continue;
            if (color != piece->color && color != PieceColor::All) continue;
            if (type != piece->type && type != PieceType::All) continue;

            vec.push_back(piece);
        }
        return vec;
    }

    std::shared_ptr<Move> ImplBoard::getMove(const Position& start_pos, const Position& end_pos) const
    {
        std::shared_ptr<MovablePiece> piece = getMovablePiece(start_pos);

        std::vector<std::shared_ptr<Move>> moves;
        piece->getMoves(moves);

        for (std::shared_ptr<Move>& move : moves)
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

    void ImplBoard::getMoves(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const
    {
        getMovablePiece(pos)->getMoves(vec);
    }

    void ImplBoard::getMoves(std::vector<std::shared_ptr<Move>>& vec) const
    {
        for (std::shared_ptr<MovablePiece> piece : pieces)
        {
            piece->getMoves(vec);
        }
    }

    PieceColor ImplBoard::getResult() const
    {
        return result;
    }

    PieceColor ImplBoard::getMoveColor() const
    {
        return moveColor;
    }
    /*
    void ImplBoard::updatePieceType(const Position& pos, PieceType new_type)
    {
        std::shared_ptr<MovablePiece> piece = pieces[piece_id];

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
    */    

    void ImplBoard::reset()
    {
        result = PieceColor::Null;
        moveColor = PieceColor::White;
        moveCounter = 0;

        for (int i = 0; i < 8; ++i)
        {
            addPiece(new Pieces::Pawn(Position(i, 1), PieceColor::White, this));

            addPiece(new Pieces::Pawn(Position(i, 6), PieceColor::Black, this));
        }

        addPiece(new Pieces::Rook(Position(0, 0), PieceColor::White, this));
        addPiece(new Pieces::Rook(Position(7, 0), PieceColor::White, this));
        addPiece(new Pieces::Knight(Position(1, 0), PieceColor::White, this));
        addPiece(new Pieces::Knight(Position(6, 0), PieceColor::White, this));
        addPiece(new Pieces::Bishop(Position(2, 0), PieceColor::White, this));
        addPiece(new Pieces::Bishop(Position(5, 0), PieceColor::White, this));
        addPiece(new Pieces::Queen(Position(4, 0), PieceColor::White, this));
        addPiece(new Pieces::King(Position(3, 0), PieceColor::White, this));

        addPiece(new Pieces::Rook(Position(0, 7), PieceColor::Black, this));
        addPiece(new Pieces::Rook(Position(7, 7), PieceColor::Black, this));
        addPiece(new Pieces::Knight(Position(1, 7), PieceColor::Black, this));
        addPiece(new Pieces::Knight(Position(6, 7), PieceColor::Black, this));
        addPiece(new Pieces::Bishop(Position(2, 7), PieceColor::Black, this));
        addPiece(new Pieces::Bishop(Position(5, 7), PieceColor::Black, this));
        addPiece(new Pieces::Queen(Position(4, 7), PieceColor::Black, this));
        addPiece(new Pieces::King(Position(3, 7), PieceColor::Black, this));

    }

    void ImplBoard::addPiece(MovablePiece* piece)
    {
        pieces.push_back(std::make_shared<MovablePiece>(piece));
    }
    /*
    void ImplBoard::updateMap()
    {
        clearBoardMap();
        buildBoardMap();
    }
    void ImplBoard::buildBoardMap()
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

    void ImplBoard::clearBoardMap()
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                boardMap[i][j] = -1;
            }
        }
    }

    void ImplBoard::clearPieces()
    {
        pieces.clear();
        pieces.push_back(nullptr);
    }*/
}

