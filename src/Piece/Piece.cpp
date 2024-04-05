#include "ChessLib/Piece/Piece.hpp"

namespace Chess
{
	IPiece::IPiece(Position pos, PieceType type, PieceColor color, std::vector<int> moveMoment, bool deleted)
		:
		pos(pos),
		type(type),
		color(color),
		moveMoment(moveMoment),
		deleted(deleted)
	{}

	IPiece::IPiece(const IPiece& right)
		:
		pos(right.pos),
		type(right.type),
		color(right.color),
		moveMoment(right.moveMoment),
		deleted(right.deleted)
	{}

	int IPiece::getDirection() const
	{
		if (color == PieceColor::Black)
			return -1;
		return 1;
	}

	int IPiece::getLastMoveMoment() const
	{
		if (moveMoment.size() == 0)
			return -1;
		return moveMoment.back();
	}

	int IPiece::getMoveCount() const
	{
		return moveMoment.size();
	}

	void IPiece::addMoveCount(int moveCnt)
	{
		moveMoment.push_back(moveCnt);
	}

	void IPiece::delMoveCount()
	{
		moveMoment.pop_back();
	}
}