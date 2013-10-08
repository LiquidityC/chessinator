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
		b.pieces[WHITE_PAWNS] 	= 0xFF00;
		b.pieces[WHITE_ROOKS] 	= 0x81;
		b.pieces[WHITE_KNIGHTS]	= 0x42;
		b.pieces[WHITE_BISHOPS]	= 0x24;
		b.pieces[WHITE_QUEEN]	= 0x8;
		b.pieces[WHITE_KING]	= 0x10;

		// Place BLACK pieces by shifting the WHITE ones
		b.pieces[BLACK_PAWNS]	= b.pieces[WHITE_PAWNS] << 40;
		b.pieces[BLACK_ROOKS]	= b.pieces[WHITE_ROOKS] << 56;
		b.pieces[BLACK_KNIGHTS]	= b.pieces[WHITE_KNIGHTS] << 56;
		b.pieces[BLACK_BISHOPS]	= b.pieces[WHITE_BISHOPS] << 56;
		b.pieces[BLACK_QUEEN]	= b.pieces[WHITE_QUEEN] << 56;
		b.pieces[BLACK_KING]	= b.pieces[WHITE_KING] << 56;

		b.pieces[ALL_WHITE_PIECES] = 0;
		b.pieces[ALL_BLACK_PIECES] = 0;

		for (int i = WHITE_PAWNS; i <= WHITE_KING; i++) {
			b.pieces[ALL_BLACK_PIECES] |= b.pieces[i];
		}
		for (int i = BLACK_PAWNS; i <= BLACK_KING; i++) {
			b.pieces[ALL_WHITE_PIECES] |= b.pieces[i];
		}
		
		b.black_castling_available = true;
		b.white_castling_available = true;
		b.piece_taken = false;

		return b;
	}

	void BoardUtil::perform_move(Move& m, Board& b)
	{
		uint64_t from, to;

		from = m.get_from_bit();
		to = m.get_to_bit();

		uint64_t& mover = get_target_for_move(from, b);
		uint64_t& target = get_target_for_move(to, b);

		assert ( &mover != &from );
		assert ( (mover & from) != 0 );

		// Perform move
		mover = mover ^ from;
		mover = mover | to;

		// Check if we 'take' a piece
		if (&target != &to) {
			target = target ^ to;
			b.piece_taken = true;
		} else {
			b.piece_taken = false;
		}

		// Recalculate the totals
		b.pieces[ALL_WHITE_PIECES] ^= to;
		b.pieces[ALL_BLACK_PIECES] ^= to;
	}

	uint64_t& BoardUtil::get_target_for_move(uint64_t& move, Board& b)
	{
		for (size_t i = WHITE_PAWNS; i <= BLACK_KING; i++) {
			if ((move & b.pieces[i]) != 0) {
				return b.pieces[i];
			}
		}

		return move;
	}
}
