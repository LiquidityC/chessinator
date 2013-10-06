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
		b.white_pawns 	= 0xFF00;
		b.white_rooks 	= 0x81;
		b.white_knights = 0x42;
		b.white_bishops	= 0x24;
		b.white_queen	= 0x8;
		b.white_king	= 0x10;

		// Place black pieces by shifting the white ones
		b.black_pawns	= b.white_pawns << 40;
		b.black_rooks	= b.white_rooks << 56;
		b.black_knights	= b.white_knights << 56;
		b.black_bishops	= b.white_bishops << 56;
		b.black_queen	= b.white_queen << 56;
		b.black_king	= b.white_king << 56;

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

		assert ( &mover != &from );
		assert ( (mover & from) != 0 );

		mover = mover ^ from;
		mover = mover | to;
	}

	int64_t& BoardUtil::get_target_for_move(int64_t& move, Board& b)
	{
		if ((move & b.white_pawns) != 0) {
			return b.white_pawns;
		} else if ((move & b.white_rooks) != 0) {
			return b.white_rooks;
		} else if ((move & b.white_knights) != 0) {
			return b.white_knights;
		} else if ((move & b.white_bishops) != 0) {
			return b.white_bishops;
		} else if ((move & b.white_king) != 0) {
			return b.white_king;
		} else if ((move & b.white_queen) != 0) {
			return b.white_queen;
		} else if ((move & b.black_pawns) != 0) {
			return b.black_pawns;
		} else if ((move & b.black_rooks) != 0) {
			return b.black_rooks;
		} else if ((move & b.black_knights) != 0) {
			return b.black_knights;
		} else if ((move & b.black_bishops) != 0) {
			return b.black_bishops;
		} else if ((move & b.black_king) != 0) {
			return b.black_king;
		} else if ((move & b.black_queen) != 0) {
			return b.black_queen;
		}

		return move;
	}
}
