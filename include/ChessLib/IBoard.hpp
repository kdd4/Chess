#pragma once

#include "ChessLib/Piece/IPieceable.hpp"
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

		PieceColor result;
		PieceColor moveColor;
		int moveCounter;

		virtual IPieceable* getPiece(const Position& pos) const = 0;
		virtual std::vector<IPieceable*> getPieces(PieceType type, PieceColor color) const = 0;

		virtual void updatePieceType(const Position& pos, PieceType) = 0;
		virtual void updateMap() = 0;
		virtual void reset() = 0;
	};
}