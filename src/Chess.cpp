#include "Chess/Chess.hpp"

namespace Chess
{
    Game::Game(Figures::Type (*getNewTypeWhite)(), Figures::Type (*getNewTypeBlack)())
        : board(new Board()), getNewTypeWhite(getNewTypeWhite), getNewTypeBlack(getNewTypeBlack) {};

    Game::Game(const Game& right)
        : board(new Board(*right.board)), getNewTypeWhite(right.getNewTypeWhite), getNewTypeBlack(right.getNewTypeBlack) {};

    Game::~Game()
    {
        board->~Board();
    };

    const Figure* Game::get(Position pos) const
    {
        return board->getFigure(pos);
    }

    int Game::getResult() const
    {
        return board->result;
    }

    const Board& Game::getBoard() const
    {
        return *board;
    }

    Game& Game::operator=(const Game& right)
    {
        delete this->board;
        this->board = new Board(*right.board);
        this->getNewTypeWhite = right.getNewTypeWhite;
        this->getNewTypeBlack = right.getNewTypeBlack;

        return *this;
    }

    bool Game::moving(Position pos1, Position pos2)
    {
        // Checking for correct positions
        if (!pos1.check() || !pos2.check()) return false;

        Figure*& movingFigure = board->getFigure(pos1);
        if (movingFigure == nullptr) return false;
        if (movingFigure->color != board->moveColor) return false;

        // Search for a move
        std::vector<Move> possibleMoves;
        movingFigure->getMoves(possibleMoves);

        Move moving;
        bool flFound = false;
        for (Move& mv : possibleMoves)
        {
            if (mv.movePos == pos2)
            {
                moving = mv;
                flFound = true;
                break;
            }
        }
        if (!flFound)
        {
            return false;
        }

        Figure* attackedFigure = nullptr;
        if (moving.attackedPos.check()) attackedFigure = board->getFigure(moving.attackedPos);

        if (!checkMove(movingFigure, attackedFigure, moving)) return false;

        // Making the move
        if (attackedFigure != nullptr) attackedFigure->deleted = true;

        movingFigure->pos = moving.movePos;
        movingFigure->lastMoveMoment = board->moveCounter;
        movingFigure->moveCount += 1;

        if (movingFigure->type == Figures::Type::King)
        {
            Position posRook;
            if (pos1.x - pos2.x == 2)
            {
                posRook = Position(0, pos1.y);
                Figure* figRook = board->getFigure(posRook);
                if (figRook == nullptr) throw excLogicalError();
                if (figRook->type != Figures::Type::Rook || figRook->color != board->moveColor || figRook->moveCount != 0)
                    throw excLogicalError();
                figRook->pos = Position(pos1.x-1, pos1.y);
            }
            else if (pos2.x - pos1.x == 2)
            {
                posRook = Position(7, pos1.y);
                Figure* figRook = board->getFigure(posRook);
                if (figRook == nullptr) throw excLogicalError();
                if (figRook->type != Figures::Type::Rook || figRook->color != board->moveColor || figRook->moveCount != 0)
                    throw excLogicalError();
                figRook->pos = Position(pos1.x+1, pos1.y);
            }
        }

        if (movingFigure->type == Figures::Type::Pawn)
        {
            if (movingFigure->pos.y == 0 || movingFigure->pos.y == 7)
            {
                Figures::Type newType = Figures::Type::Pawn;
                while(newType == Figures::Type::Pawn || newType == Figures::Type::King)
                    newType = (board->moveColor == Color::White) ? getNewTypeWhite() : getNewTypeBlack();

                Figure* prevFig = movingFigure;
                updateFigure(movingFigure, newType);
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
                attackedFigure = nullptr;
                if (mv.attackedPos.check()) attackedFigure = board->getFigure(mv.attackedPos);
                if (checkMove(enemyFigure, attackedFigure, mv))
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
                if (enemyKing->pos == mv.attackedPos)
                {
                    result = board->moveColor*(-1);
                    break;
                }
            }
            board->result = result;
        }

        return true;
    }

    bool Game::checkMove(Figure* movingFigure, Figure* attackedFigure, Move moving)
    {
        // Saving variables for canceling the move
        int prevLastMoveMoment = movingFigure->lastMoveMoment;
        Position pos1 = movingFigure->pos;
        Position pos2 = moving.movePos;

        // Making the move
        if (attackedFigure != nullptr) attackedFigure->deleted = true;

        movingFigure->pos = moving.movePos;
        movingFigure->lastMoveMoment = board->moveCounter;
        movingFigure->moveCount += 1;

        Figure* figRook = nullptr;
        Position prevPosRook;
        if (movingFigure->type == Figures::Type::King)
        {
            if (pos1.x - pos2.x == 2)
            {
                Position posRook = Position(0, pos1.y);
                figRook = board->getFigure(posRook);
                if (figRook == nullptr) throw excLogicalError();
                if (figRook->type != Figures::Type::Rook || figRook->color != board->moveColor || figRook->moveCount != 0)
                    throw excLogicalError();
                prevPosRook = figRook->pos;
                figRook->pos = Position(pos1.x-1, pos1.y);
            }
            else if (pos2.x - pos1.x == 2)
            {
                Position posRook = Position(7, pos1.y);
                figRook = board->getFigure(posRook);
                if (figRook == nullptr) throw excLogicalError();
                if (figRook->type != Figures::Type::Rook || figRook->color != board->moveColor || figRook->moveCount != 0)
                    throw excLogicalError();
                prevPosRook = figRook->pos;
                figRook->pos = Position(pos1.x+1, pos1.y);
            }
        }

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
            if (ourKing->pos == mv.attackedPos)
            {
                check = false;
                break;
            }
        }

        // Canceling the move
        if (attackedFigure != nullptr) attackedFigure->deleted = false;

        movingFigure->pos = pos1;
        movingFigure->lastMoveMoment = prevLastMoveMoment;
        movingFigure->moveCount -= 1;

        if (figRook != nullptr) figRook->pos = prevPosRook;
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
            newFigure = new Figures::Pawn(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Rook:
            newFigure = new Figures::Rook(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Knight:
            newFigure = new Figures::Knight(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Bishop:
            newFigure = new Figures::Bishop(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->deleted);
            break;
        case Figures::Type::Queen:
            newFigure = new Figures::Queen(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->deleted);
            break;
        case Figures::Type::King:
            newFigure = new Figures::King(figure->pos, figure->color, figure->board, figure->moveCount, figure->lastMoveMoment, figure->deleted);
            break;
        default:
            throw excLogicalError();
        }
        figure = newFigure;
    }
}

