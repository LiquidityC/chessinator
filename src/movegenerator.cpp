#include "movegenerator.h"

namespace cengine
{
	void MoveGenerator::calculate_moves_for(const Board& b)
	{
		// Fill the local vector
		calculate_pawn_moves_for(b);
		calculate_rook_moves_for(b);
		calculate_knight_moves_for(b);
		calculate_bishop_moves_for(b);
		calculate_queen_moves_for(b);
		calculate_king_moves_for(b);
	}

	void MoveGenerator::calculate_pawn_moves_for(const Board& b)
	{
		// Stub
	}

	void MoveGenerator::calculate_rook_moves_for(const Board& b)
	{
		// Stub
	}

	void MoveGenerator::calculate_knight_moves_for(const Board& b)
	{
		// Stub
	}

	void MoveGenerator::calculate_bishop_moves_for(const Board& b)
	{
		// Stub
	}

	void MoveGenerator::calculate_queen_moves_for(const Board& b)
	{
		// Stub
	}

	void MoveGenerator::calculate_king_moves_for(const Board& b)
	{
		// Stub
	}
}
