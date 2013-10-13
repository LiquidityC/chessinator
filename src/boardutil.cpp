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
			b.pieces[ALL_WHITE_PIECES] |= b.pieces[i];
		}
		for (int i = BLACK_PAWNS; i <= BLACK_KING; i++) {
			b.pieces[ALL_BLACK_PIECES] |= b.pieces[i];
		}
		
		b.black_long_castling_available = true;
		b.black_short_castling_available = true;
		b.white_long_castling_available = true;
		b.white_short_castling_available = true;
		b.piece_taken = false;
		b.whites_turn = true;

		return b;
	}

	void BoardUtil::perform_move(const Move& m, Board& b)
	{
		if (m.is_castling_move()) {
			perform_castling_move(m, b);
		} else {
			perform_regular_move(m, b);
		}
	}

	void BoardUtil::perform_castling_move(const Move& m, Board& b)
	{
		Move* second;

		if (m.get_to_coord() == "g1") {
			second = new Move("h1", "f1");
		} else if(m.get_to_coord() == "c1") {
			second = new Move("a1", "d1");
		} else if(m.get_to_coord() == "g8") {
			second = new Move("h8", "f8");
		} else if(m.get_to_coord() == "c8") {
			second = new Move("a8", "d8");
		}

		perform_regular_move(m, b);
		perform_regular_move(*second, b);

		delete second;
	}

	void BoardUtil::perform_regular_move(const Move& m, Board& b)
	{
		uint64_t from, to;

		from = m.get_from_bit();
		to = m.get_to_bit();

		Units mover = get_target_for_move(from, b);
		Units target = get_target_for_move(to, b);

		assert ( mover != PIECES_SIZE );
		assert ( (b.pieces[mover] & from) != 0 );

		// Perform move
		b.pieces[mover] ^= from;
		b.pieces[mover] |= to;

		// Check if we 'take' a piece
		if (target != PIECES_SIZE) {
			b.pieces[target] ^= to;
			b.piece_taken = true;
		} else {
			b.piece_taken = false;
		}

		// Recalculate the totals
		// From
		if ((b.pieces[ALL_WHITE_PIECES] & from) != 0) {
			b.pieces[ALL_WHITE_PIECES] ^= from;
		} else {
			b.pieces[ALL_BLACK_PIECES] ^= from;
		}

		// To
		b.pieces[ALL_WHITE_PIECES] ^= to;
		b.pieces[ALL_BLACK_PIECES] ^= to;

		check_castling_impact(m, b);
	}

	void BoardUtil::check_castling_impact(const Move& m, Board& b)
	{
		uint64_t from = m.get_from_bit();

		switch (from) {
			case static_cast<uint64_t>(0x10):
				b.white_short_castling_available = false;
				b.white_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x1):
				b.white_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x80):
				b.white_short_castling_available = false;
				break;
			case static_cast<uint64_t>(0x10)<<54:
				b.black_short_castling_available = false;
				b.black_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x1)<<54:
				b.black_long_castling_available = false;
				break;
			case static_cast<uint64_t>(0x80)<<54:
				b.black_short_castling_available = false;
				break;
		}
	}

	Units BoardUtil::get_target_for_move(uint64_t& move, Board& b)
	{
		for (unsigned int i = WHITE_PAWNS; i <= BLACK_KING; i++) {
			if ((move & b.pieces[i]) != 0) {
				return static_cast<Units>(i);
			}
		}

		return PIECES_SIZE;
	}
}
