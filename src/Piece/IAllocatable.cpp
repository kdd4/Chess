#include "ChessLib/Piece/IAllocatable.hpp"

namespace Chess
{
	IAllocatable::IAllocatable(IBoard* board)
		:
		board(board)
	{}

	IAllocatable::IAllocatable(const IAllocatable& right)
		:
		board(right.board)
	{}
}