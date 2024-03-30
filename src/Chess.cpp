#include "ChessLib/Chess.hpp"

namespace Chess
{
    Chess::Chess(PieceType (*getNewTypeWhite)(), PieceType (*getNewTypeBlack)())
        : board(new Board()), getNewTypeWhite(getNewTypeWhite), getNewTypeBlack(getNewTypeBlack) {}

    Chess::Chess(const Chess& right)
        : board(new Board(*right.board)), getNewTypeWhite(right.getNewTypeWhite), getNewTypeBlack(right.getNewTypeBlack) {}

    Chess::~Chess()
    {
        board->~Board();
    }

    const IPieceable* Chess::get(Position pos) const
    {
        return board->getPiece(pos);
    }

    PieceColor Chess::getResult() const
    {
        return board->result;
    }

    const Board& Chess::getBoard() const
    {
        return *board;
    }

    Chess& Chess::operator=(const Chess& right)
    {
        delete this->board;
        this->board = new Board(*right.board);
        this->getNewTypeWhite = right.getNewTypeWhite;
        this->getNewTypeBlack = right.getNewTypeBlack;

        return *this;
    }
    /*
    void Game::makeMove(Move& moving)
    {
        if (moving.attackedFigure != nullptr) moving.attackedFigure->deleted = true;

        Figure* figure = board->getFigure(moving.moving.figurePos);
        if (figure != moving.moving.figure) throw excLogicalError();
        figure->pos = moving.moving.newPos;
        figure->prevLastMoveMoment = figure->lastMoveMoment;
        figure->lastMoveMoment = board->moveCounter;
        figure->moveCount += 1;

        for (MoveEvent& event : moving.additionalMoving)
        {
            figure = board->getFigure(event.figurePos);
            if (event.figure != figure) throw excLogicalError();
            figure->pos = event.newPos;
            figure->prevLastMoveMoment = figure->lastMoveMoment;
            figure->lastMoveMoment = board->moveCounter;
            figure->moveCount += 1;
        }
    }

    void Game::cancelMove(Move& moving)
    {
        if (moving.attackedFigure != nullptr) moving.attackedFigure->deleted = false;

        Figure* figure = board->getFigure(moving.moving.newPos);
        if (figure != moving.moving.figure) throw excLogicalError();
        figure->pos = moving.moving.figurePos;
        figure->lastMoveMoment = figure->prevLastMoveMoment;
        figure->prevLastMoveMoment = -1;
        figure->moveCount -= 1;

        for (MoveEvent& event : moving.additionalMoving)
        {
            figure = board->getFigure(event.newPos);
            if (event.figure != figure) throw excLogicalError();
            figure->pos = event.figurePos;
            figure->lastMoveMoment = figure->prevLastMoveMoment;
            figure->prevLastMoveMoment = -1;
            figure->moveCount -= 1;
        }
    }*/

    bool Chess::moving(Position pos1, Position pos2)
    {
        // Checking for correct positions
        if (!pos1.check() || !pos2.check()) return false;

        IPieceable* movingPiece = board->getPiece(pos1);
        if (movingPiece == nullptr) return false;
        if (movingPiece->color != board->moveColor) return false;

        // Search for a move
        IMove* moving = board->getMove(pos1, pos2);

        if (!moving)
        {
            return false;
        }

        if (!checkMove(movingPiece, moving)) return false;

        // Making the move
        makeMove(moving);

        if (movingPiece->type == Figures::Type::Pawn)
        {
            if (movingPiece->pos.y == 0 || movingPiece->pos.y == 7)
            {
                Figures::Type newType = Figures::Type::Pawn;
                while(newType == Figures::Type::Pawn || newType == Figures::Type::King)
                    newType = (board->moveColor == Color::White) ? getNewTypeWhite() : getNewTypeBlack();

                Figure* prevFig = movingPiece;
                updateFigure(movingPiece, newType);
                delete prevFig;
            }
        }

        board->moveColor *= -1;
        board->moveCounter += 1;
        board->update();

        // End-of-game check
        bool endGame = true;
        for (Figure* enemyFigure : board->findFigures(Figures::Type::Null, board->moveColor))
        {
            std::vector<Move> moves;
            enemyFigure->getMoves(moves);

            for (Move& mv : moves)
            {
                if (checkMove(enemyFigure, mv))
                {
                    endGame = false;
                    break;
                }
            }
            if (!endGame) break;
        }

        if (endGame)
        {
            std::vector<Move> ourMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, board->moveColor*(-1)), true);
            Figure* enemyKing = board->findFigures(Figures::Type::King, board->moveColor)[0];

            int result = Color::Both;
            for (Move& mv : ourMoves)
            {
                if (mv.attackedFigure == nullptr) continue;
                if (enemyKing == mv.attackedFigure)
                {
                    result = board->moveColor*(-1);
                    break;
                }
            }
            board->result = result;
        }

        return true;
    }

    /*
    bool Game::checkMove(Figure* movingFigure, Move& moving)
    {
        // Making the move
        makeMove(moving);

        Figure* prevFig = nullptr;
        if (movingFigure->type == Figures::Type::Pawn)
        {
            if (movingFigure->pos.y == 0 || movingFigure->pos.y == 7)
            {
                Figures::Type newType = Figures::Type::Pawn;
                while(newType == Figures::Type::Pawn || newType == Figures::Type::King)
                    newType = (board->moveColor == Color::White) ? getNewTypeWhite() : getNewTypeBlack();
                prevFig = movingFigure;
                updateFigure(movingFigure, newType);
            }
        }

        board->moveColor *= -1;
        board->moveCounter += 1;
        board->update();

        // Checking the move
        std::vector<Move> enemyMoves = board->getAllMoves(board->findFigures(Figures::Type::Null, board->moveColor), true);
        Figure* ourKing = board->findFigures(Figures::Type::King, board->moveColor*(-1))[0];

        bool check = true;
        for (Move& mv : enemyMoves)
        {
            if (ourKing == mv.attackedFigure)
            {
                check = false;
                break;
            }
        }

        // Canceling the move
        cancelMove(moving);

        if (prevFig != nullptr)
        {
            delete movingFigure;
            movingFigure = prevFig;
        }

        board->moveColor *= -1;
        board->moveCounter -= 1;
        board->update();

        return check;
    }

    void Game::updateFigure(Figure*& figure, Figures::Type newType)
    {
        Figure* newFigure;
        switch(newType)
        {
        case Figures::Type::Pawn:
            newFigure = new Figures::Pawn(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->prevLastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Rook:
            newFigure = new Figures::Rook(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->prevLastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Knight:
            newFigure = new Figures::Knight(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->prevLastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Bishop:
            newFigure = new Figures::Bishop(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->prevLastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Queen:
            newFigure = new Figures::Queen(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->prevLastMoveMoment, figure->deleted);
            break;
        case Figures::Type::King:
            newFigure = new Figures::King(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->prevLastMoveMoment, figure->deleted);
            break;
        default:
            throw excLogicalError();
        }
        figure = newFigure;
    }*/
}

