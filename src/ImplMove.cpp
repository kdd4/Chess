#include "ChessLib/ImplMove.hpp"

namespace Chess
{
	ImplMove::ImplMove(std::weak_ptr<Board> board) :
		board(board),
		moveCnt(board.lock()->getMoveCount())
	{}

	const std::map<Position, Position>& ImplMove::getSteps() const
	{
		return steps;
	}

	const std::set<Position>& ImplMove::getAttackedPositions() const
	{
		return attacked_positions;
	}

	const std::map<Position, std::pair<PieceType, PieceType>>& ImplMove::getTypeChanges() const
	{
		return type_changes;
	}

	int ImplMove::getMoveCount() const
	{
		return moveCnt;
	}

	void ImplMove::appendStep(Position old_pos, Position new_pos)
	{
		steps.insert(std::make_pair(old_pos, new_pos));
	}

	void ImplMove::appendAttack(Position attacked_pos)
	{
		attacked_positions.insert(attacked_pos);
	}

	void ImplMove::changeType(Position cur_pos, PieceType old_type, PieceType new_type)
	{
		type_changes.insert(std::make_pair(cur_pos, std::make_pair(old_type,new_type)));
	}
}
