#include "ChessLib/Piece/IPieceable.hpp"

namespace Chess
{
	IPieceable::IPieceable(Position pos, PieceType type, PieceColor color, std::vector<int> moveMoment, bool deleted)
		:
		pos(pos),
		type(type),
		color(color),
		moveMoment(moveMoment),
		deleted(deleted)
	{}

	IPieceable::IPieceable(const IPieceable& right)
		:
		pos(right.pos),
		type(right.type),
		color(right.color),
		moveMoment(right.moveMoment),
		deleted(right.deleted)
	{}

	int IPieceable::getDirection() const
	{
		if (color == PieceColor::Black)
			return -1;
		return 1;
	}

	int IPieceable::getLastMoveMoment() const
	{
		return moveMoment.back();
	}
}