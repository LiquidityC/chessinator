#ifndef _BOARD_H
#define _BOARD_H

#include <cstdint>

namespace cengine
{
	// 64 bits cover the amount of squares on the board
	typedef struct {
			int64_t black_pawns, white_pawns;
			int64_t black_rooks, white_rooks;
			int64_t black_bishops, white_bishops;
			int64_t black_knights, white_knights;
			int64_t black_queen, white_queen;
			int64_t black_king, white_king;
			bool white_castling_available, black_castling_available;
	} Board;
}

#endif
