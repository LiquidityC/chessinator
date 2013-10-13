#ifndef _BOARD_H
#define _BOARD_H

#include <cstdint>

namespace cengine
{
	enum Units {
		WHITE_PAWNS,
		WHITE_ROOKS,
		WHITE_KNIGHTS,
		WHITE_BISHOPS,
		WHITE_QUEEN,
		WHITE_KING,
		BLACK_PAWNS,
		BLACK_ROOKS,
		BLACK_KNIGHTS,
		BLACK_BISHOPS,
		BLACK_QUEEN,
		BLACK_KING,
		ALL_WHITE_PIECES,
		ALL_BLACK_PIECES,
		PIECES_SIZE
	};

	// 64 bits cover the amount of squares on the board
	typedef struct {
		uint64_t pieces[PIECES_SIZE];
		bool white_long_castling_available, black_long_castling_available;
		bool white_short_castling_available, black_short_castling_available;
		bool piece_taken;
		bool whites_turn;
	} Board;
}

#endif
