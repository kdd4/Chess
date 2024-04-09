#include "ChessLib/Chess.hpp"

namespace Chess
{
    Chess::Chess(PieceType (*getNewTypeWhite)(), PieceType (*getNewTypeBlack)())
        : 
        board(new ImplBoard()),
        result(PieceColor::Null),
        getNewTypeWhite(getNewTypeWhite),
        getNewTypeBlack(getNewTypeBlack)
    {}

    Chess::Chess(const Chess& right)
        : 
        board(new ImplBoard(*(right.board))),
        result(right.result),
        getNewTypeWhite(right.getNewTypeWhite),
        getNewTypeBlack(right.getNewTypeBlack)
    {}

    const std::shared_ptr<Piece> Chess::get(Position pos) const
    {
        return board->getPiece(pos);
    }

    PieceColor Chess::getResult() const
    {
        return result;
    }

    const std::shared_ptr<Board> Chess::getBoard() const
    {
        return board;
    }

    Chess& Chess::operator=(const Chess& right)
    {
        board = std::shared_ptr<ImplBoard>(new ImplBoard(*right.board));
        this->getNewTypeWhite = right.getNewTypeWhite;
        this->getNewTypeBlack = right.getNewTypeBlack;

        return *this;
    }

    bool Chess::moving(Position pos1, Position pos2)
    {
        // Checking for correct positions
        if (!pos1.check() || !pos2.check()) return false;

        std::shared_ptr<MovablePiece> movingPiece = board->getMovablePiece(pos1);
        if (movingPiece == nullptr) return false;
        if (movingPiece->color != board->getMoveColor()) return false;

        // Search for a move
        std::vector<std::shared_ptr<Move>> moves;
        movingPiece->getMoves(moves);

        std::shared_ptr<Move> move;
        for (std::shared_ptr<Move> ref_move : moves)
        {
            try
            {
                if (ref_move->getSteps().at(pos1) != pos2) 
                    continue;

                move = ref_move;
                break;
            }
            catch (std::out_of_range&) {}
        }

        if (!move) return false;

        PieceColor ourColor = board->getMoveColor();
        std::shared_ptr<Piece> ourKing = board->getPieces(PieceType::King, ourColor).at(0);

        board->makeMove(move);

        // Checking the move
        PieceColor enemyColor = board->getMoveColor();

        std::vector<std::shared_ptr<Move>> enemyMoves;
        board->getMoves(enemyMoves, enemyColor);

        for (std::shared_ptr<Move>& enemyMove : enemyMoves)
        {
            for (const Position& attackedPos : enemyMove->getAttackedPositions())
            {
                if (attackedPos == ourKing->pos)
                {
                    board->cancelMove(move);
                    return false;
                }
            }
        }

        // End-of-game check
        bool endGame = true;

        for (std::shared_ptr<Move>& enemyMove : enemyMoves)
        {
            if (checkMove(enemyMove))
            {
                endGame = false;
                break;
            }
        }

        if (!endGame) return true;

        std::vector<std::shared_ptr<Move>> ourAttackMoves;
        board->getAttackMoves(ourAttackMoves, ourColor);

        std::shared_ptr<Piece> enemyKing = board->getPieces(PieceType::King, enemyColor).at(0);

        PieceColor result = PieceColor::All;
        for (std::shared_ptr<Move>& outAttackMove : ourAttackMoves)
        {
            for (const Position& attackedPos : outAttackMove->getAttackedPositions())
            {
                if (attackedPos == enemyKing->pos)
                {
                    result = ourColor;
                    break;
                }
            }

            if (result != PieceColor::All)
                break;
        }
        this->result = result;

        return true;
    }

    
    bool Chess::checkMove(std::shared_ptr<Move> move)
    {
        // Getting our king
        std::shared_ptr<Piece> ourKing = board->getPieces(PieceType::King, board->getMoveColor()).at(0);

        // Making the move
        board->makeMove(move);

        // Checking the move
        std::vector<std::shared_ptr<Move>> enemyMoves;
        PieceColor enemyColor = board->getMoveColor();
        board->getAttackMoves(enemyMoves, enemyColor);

        bool check = true;
        for (std::shared_ptr<Move>& enemyMove : enemyMoves)
        {
            for (const Position& attackedPos : enemyMove->getAttackedPositions())
            {
                if (attackedPos == ourKing->pos)
                {
                    check = false;
                    break;
                }
            }

            if (check) break;
        }

        // Canceling the move
        board->cancelMove(move);

        return check;
    }
}

