#include "ChessLib/ImplBoard.hpp"

namespace Chess
{
    ImplBoard::ImplBoard() :
        Pieces({}),
        MoveCounter(-1)
    {
        reset();
    }

    ImplBoard::ImplBoard(const ImplBoard& right)
        :
        Pieces({}),
        MoveCounter(right.MoveCounter)
    {
        for (std::shared_ptr<MovablePiece> piece : right.Pieces)
        {
            Pieces.push_back(piece->clone(std::shared_ptr<Board>(this)));
        }
    }

    int ImplBoard::getPieceId(const Position& pos, int moveMoment, bool deleted) const
    {
        for (int i = 0; i < Pieces.size(); ++i)
        {
            if (Pieces[i]->deleted != deleted) continue;
            if (Pieces[i]->pos != pos) continue;
            if (moveMoment != -1)
            {
                if (Pieces[i]->getLastMoveMoment() != moveMoment) continue;
            }
            return i;
        }
        return -1;
    }

    std::shared_ptr<MovablePiece> ImplBoard::getMovablePiece(const Position& pos, int moveMoment, bool deleted) const
    {
        int id = getPieceId(pos, moveMoment, deleted);

        return (id != -1) ? Pieces[id] : nullptr;
    }

    void ImplBoard::getAttackMoves(std::vector<std::shared_ptr<Move>>& vec, const PieceColor color) const
    {
        for (std::shared_ptr<MovablePiece> piece : Pieces)
        {
            if (color != PieceColor::All)
            {
                if (piece->color != color)
                    continue;
            }
            piece->getMoves(vec, true);
        }
    }

    std::shared_ptr<Piece> ImplBoard::getPiece(const Position& pos) const
    {
        return getMovablePiece(pos);
    }

    std::vector<std::shared_ptr<Piece>> ImplBoard::getPieces(PieceType type, PieceColor color) const
    {
        std::vector<std::shared_ptr<Piece>> vec;
        for (std::shared_ptr<Piece> piece : Pieces)
        {
            if (piece == nullptr) continue;
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

    void ImplBoard::getMoves(std::vector<std::shared_ptr<Move>>& vec, const PieceColor color) const
    {
        for (std::shared_ptr<MovablePiece> piece : Pieces)
        {
            if (color != PieceColor::All)
            {
                if (piece->color != color)
                    continue;
            }
            piece->getMoves(vec);
        }
    }

    PieceColor ImplBoard::getMoveColor() const
    {
        return (MoveCounter & 1) ? PieceColor::Black : PieceColor::White;
    }

    int ImplBoard::getMoveCount() const
    {
        return MoveCounter;
    }

    void ImplBoard::makeMove(const std::shared_ptr<Move> move)
    {
        if (MoveCounter != move->getMoveCount())
            return;

        for (const Position& attacked_pos : move->getAttackedPositions())
        {
            std::shared_ptr<Piece> attacked_piece = getPiece(attacked_pos);

            if (attacked_piece == nullptr) continue;

            if (attacked_piece->deleted == true)
            {
                throw std::logic_error("Failure attacking");
            }

            attacked_piece->deleted = true;
            attacked_piece->addMoveCount(MoveCounter);
        }

        for (const auto& type_change : move->getTypeChanges())
        {
            std::shared_ptr<Piece> piece = getPiece(type_change.first);

            if (piece == nullptr)
            {
                throw std::logic_error("Type changing failure");
            }

            changeType(type_change.first, type_change.second.second);
            piece->addMoveCount(MoveCounter);
        }

        for (const std::pair<Position, Position>& step : move->getSteps())
        {
            std::shared_ptr<Piece> piece = getPiece(step.first);

            if (piece == nullptr)
            {
                throw std::logic_error("Piece isn't found");
            }

            piece->pos = step.second;
            piece->addMoveCount(MoveCounter);
        }

        MoveCounter += 1;
    }

    void ImplBoard::cancelMove(const std::shared_ptr<Move> move)
    {
        if (MoveCounter - 1 != move->getMoveCount())
            return;

        for (const std::pair<Position, Position>& step : move->getSteps())
        {
            std::shared_ptr<Piece> piece = getPiece(step.second);

            if (piece == nullptr)
            {
                throw std::logic_error("Piece isn't found");
            }

            if (piece->getMoveCount() != MoveCounter - 1)
                continue;

            piece->pos = step.first;
            piece->delMoveCount();
        }

        for (const auto& type_change : move->getTypeChanges())
        {
            std::shared_ptr<Piece> piece = getPiece(type_change.first);

            if (piece == nullptr)
            {
                throw std::logic_error("Type changing failure");
            }

            if (piece->getMoveCount() != MoveCounter - 1)
                continue;

            changeType(type_change.first, type_change.second.first);
            piece->delMoveCount();
        }

        for (const Position& attacked_pos : move->getAttackedPositions())
        {
            std::shared_ptr<Piece> attacked_piece = getMovablePiece(attacked_pos, MoveCounter - 1, true);

            if (attacked_piece == nullptr) continue;

            if (attacked_piece->getMoveCount() != MoveCounter - 1)
                continue;

            if (attacked_piece->deleted == false)
            {
                throw std::logic_error("Failure attacking reset");
            }

            attacked_piece->deleted = false;
            attacked_piece->delMoveCount();
        }

        MoveCounter -= 1;
    }

    
    void ImplBoard::changeType(const Position& pos, const PieceType type)
    {
        int piece_id = getPieceId(pos);

        if (piece_id == -1)
            throw std::logic_error("Type changing failure");

        std::shared_ptr<MovablePiece>& piece = Pieces[piece_id];

        std::shared_ptr<MovablePiece> new_piece;

        switch (type)
        {
        case PieceType::Pawn:
            new_piece = std::shared_ptr<MovablePiece>(new Pieces::Pawn(*piece));
            break;

        case PieceType::Rook:
            new_piece = std::shared_ptr<MovablePiece>(new Pieces::Rook(*piece));
            break;

        case PieceType::Knight:
            new_piece = std::shared_ptr<MovablePiece>(new Pieces::Knight(*piece));
            break;

        case PieceType::Bishop:
            new_piece = std::shared_ptr<MovablePiece>(new Pieces::Bishop(*piece));
            break;

        case PieceType::Queen:
            new_piece = std::shared_ptr<MovablePiece>(new Pieces::Queen(*piece));
            break;

        case PieceType::King:
            new_piece = std::shared_ptr<MovablePiece>(new Pieces::King(*piece));
            break;

        default:
            throw std::logic_error("Type changing failure: wrong type");
            break;
        }

        Pieces[piece_id].swap(new_piece);
    } 

    void ImplBoard::reset()
    {
        MoveCounter = 0;

        std::weak_ptr<Board> brd(std::shared_ptr<Board>(this));

        for (int i = 0; i < 8; ++i)
        {
            addPiece(new Pieces::Pawn(Position(i, 1), PieceColor::White, brd));

            addPiece(new Pieces::Pawn(Position(i, 6), PieceColor::Black, brd));
        }

        addPiece(new Pieces::Rook(Position(0, 0), PieceColor::White, brd));
        addPiece(new Pieces::Rook(Position(7, 0), PieceColor::White, brd));
        addPiece(new Pieces::Knight(Position(1, 0), PieceColor::White, brd));
        addPiece(new Pieces::Knight(Position(6, 0), PieceColor::White, brd));
        addPiece(new Pieces::Bishop(Position(2, 0), PieceColor::White, brd));
        addPiece(new Pieces::Bishop(Position(5, 0), PieceColor::White, brd));
        addPiece(new Pieces::Queen(Position(4, 0), PieceColor::White, brd));
        addPiece(new Pieces::King(Position(3, 0), PieceColor::White, brd));

        addPiece(new Pieces::Rook(Position(0, 7), PieceColor::Black, brd));
        addPiece(new Pieces::Rook(Position(7, 7), PieceColor::Black, brd));
        addPiece(new Pieces::Knight(Position(1, 7), PieceColor::Black, brd));
        addPiece(new Pieces::Knight(Position(6, 7), PieceColor::Black, brd));
        addPiece(new Pieces::Bishop(Position(2, 7), PieceColor::Black, brd));
        addPiece(new Pieces::Bishop(Position(5, 7), PieceColor::Black, brd));
        addPiece(new Pieces::Queen(Position(4, 7), PieceColor::Black, brd));
        addPiece(new Pieces::King(Position(3, 7), PieceColor::Black, brd));
    }

    void ImplBoard::addPiece(MovablePiece* piece)
    {
        if (Pieces.size() == 0) 
            Pieces = { std::shared_ptr<MovablePiece>(piece) };
        else
            Pieces.push_back(std::shared_ptr<MovablePiece>(piece));
    }
}
