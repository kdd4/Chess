#include "ChessLib/IBoard.hpp"

namespace Chess
{
	IBoard::IBoard()
		:
		result(PieceColor::Null),
		moveColor(PieceColor::Null),
		moveCounter(0)
	{}

	IBoard::IBoard(PieceColor result, PieceColor moveColor, int moveCounter)
		:
		result(result),
		moveColor(moveColor),
		moveCounter(moveCounter)
	{}

	IBoard::IBoard(const IBoard& right)
		:
		result(right.result),
		moveColor(right.moveColor),
		moveCounter(right.moveCounter)
	{}
}