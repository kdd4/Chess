#pragma once

#include <vector>

#include "ChessLib/Piece/IPieceable.hpp"
#include "ChessLib/IMove.hpp"

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

namespace Chess
{
	class IBoard
	{
	public:
		IBoard();
		IBoard(PieceColor result, PieceColor moveColor, int moveCounter);
		IBoard(const IBoard& right);

		virtual IPieceable* getPiece(const Position& pos) const = 0;
		virtual std::vector<IPieceable*> getPieces(PieceType type, PieceColor color) const = 0;

		virtual IMove* getMove(const Position& start_pos, const Position& end_pos) const = 0;
		virtual void getMoves(const Position& pos, std::vector<IMove*>& vec) const = 0;
		virtual void getMoves(std::vector<IMove*>& vec) const = 0;

		virtual void updatePieceType(const Position& pos, const PieceType type) = 0;
		virtual void updateMap() = 0;
		virtual void reset() = 0;

		PieceColor result;
		PieceColor moveColor;
		int moveCounter;
	};
}