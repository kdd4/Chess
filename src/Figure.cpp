#include "Chess/Figure.hpp"

namespace Chess
{
    Figure::Figure(Position position, int color, Figures::Type type, Board* board, int moveCount, int lastMoveMoment, int prevLastMoveMoment, bool deleted) :
        pos(position),
        color(color),
        lastMoveMoment(lastMoveMoment),
        prevLastMoveMoment(prevLastMoveMoment),
        moveCount(moveCount),
        deleted(deleted),
        board(board),
        type(type)
    {}

    Figure::~Figure() {};
}
