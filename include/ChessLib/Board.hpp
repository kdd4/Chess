#pragma once

#include "ChessLib/Piece/Piece.hpp"
#include "ChessLib/Move.hpp"

#include "ChessLib/Piece/Enums.hpp"
#include "ChessLib/Position.hpp"

#include <vector>
#include <memory>

namespace Chess
{
	class IBoard
	{
	public:
		virtual std::shared_ptr<Piece> getPiece(const Position& pos) const = 0;
		virtual std::vector<std::shared_ptr<Piece>> getPieces(PieceType type, PieceColor color) const = 0;

		virtual std::shared_ptr<Move> getMove(const Position& start_pos, const Position& end_pos) const = 0;
		virtual void getMoves(const Position& pos, std::vector<std::shared_ptr<Move>>& vec) const = 0;
		virtual void getMoves(std::vector<std::shared_ptr<Move>>& vec) const = 0;

		virtual PieceColor getResult() const = 0;
		virtual PieceColor getMoveColor() const = 0;
		virtual int getMoveCount() const = 0;
	};

	typedef IBoard Board;
}