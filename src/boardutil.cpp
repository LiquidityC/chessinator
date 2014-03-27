#include "controlcalculator.h"
#include "boardutil.h"
#include "board.h"

namespace cengine
{
	uint64_t BoardUtil::shift_piece(const uint64_t piece, const Direction direction)
	{
		switch(direction)
		{
			case UP:
				return piece << 8;
			case UP_RIGHT:
				return piece << 9;
			case RIGHT:
				return piece << 1;
			case DOWN_RIGHT:
				return piece >> 7;
			case DOWN:
				return piece >> 8;
			case DOWN_LEFT:
				return piece >> 9;
			case LEFT:
				return piece >> 1;
			case UP_LEFT:
				return piece << 7;
			default:
				return piece;
		}
	}

	bool BoardUtil::is_white_in_check(const Board& board)
	{
		ControlCalculator cc;
		uint64_t king = board.get_pieces_for(Unit::WHITE_KING);
		return (cc.calculate_black_controlzone_for(board) & king) != 0;
	}

	bool BoardUtil::is_black_in_check(const Board& board)
	{
		ControlCalculator cc;
		uint64_t king = board.get_pieces_for(Unit::BLACK_KING);
		return (cc.calculate_white_controlzone_for(board) & king) != 0;
	}
}
