#include <cstdlib>
#include <cassert>

#include "boardutil.h"
#include "move.h"

namespace cengine
{
	Board BoardUtil::create_board()
	{
		/**
		 * We set initial placement for all pieces.
		 * Placement is held in binary where th 1 bit co-relates
		 * to the bottom left square of the board
		 */
		Board b;

		// Place white pieces
		b.units[WHITE_PAWNS] 	= 0xFF00;
		b.units[WHITE_ROOKS] 	= 0x81;
		b.units[WHITE_KNIGHTS] 	= 0x42;
		b.units[WHITE_BISHOPS]	= 0x24;
		b.units[WHITE_QUEEN]	= 0x8;
		b.units[WHITE_KING]		= 0x10;

		// Place BLACK pieces by shifting the WHITE ones
		b.units[BLACK_PAWNS]	= b.units[WHITE_PAWNS] << 40;
		b.units[BLACK_ROOKS]	= b.units[WHITE_ROOKS] << 56;
		b.units[BLACK_KNIGHTS]	= b.units[WHITE_KNIGHTS] << 56;
		b.units[BLACK_BISHOPS]	= b.units[WHITE_BISHOPS] << 56;
		b.units[BLACK_QUEEN]	= b.units[WHITE_QUEEN] << 56;
		b.units[BLACK_KING]		= b.units[WHITE_KING] << 56;

		b.black_castling_available = true;
		b.white_castling_available = true;

		return b;
	}

	void BoardUtil::perform_move(Move& m, Board& b)
	{
		int64_t from, to;

		from = m.get_from_bit();
		to = m.get_to_bit();

		int64_t& mover = get_target_for_move(from, b);
		int64_t& target = get_target_for_move(to, b);

		assert ( &mover != &from );
		assert ( (mover & from) != 0 );

		// Perform move
		mover = mover ^ from;
		mover = mover | to;

		// Check if we 'take' a piece
		if (&target != &to) {
			target = target ^ to;
		}
	}

	int64_t& BoardUtil::get_target_for_move(int64_t& move, Board& b)
	{
		for (size_t i = WHITE_PAWNS; i < UNIT_TYPE_COUNT; i++) {
			if ((move & b.units[i]) != 0) {
				return b.units[i];
			}
		}

		return move;
	}
}
