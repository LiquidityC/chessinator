#ifndef _BOARD_UTIL_H
#define _BOARD_UTIL_H

#include <cstdint>

#define WHITE_SQUARES 	0x55AA55AA55AA55AA
#define BLACK_SQUARES 	0xAA55AA55AA55AA55

#define LEFT_COL     	0x0101010101010101
#define COL_B			0x0202020202020202
#define COL_G			0x4040404040404040
#define RIGHT_COL		0x8080808080808080

#define TOP_ROW       	0xFF00000000000000
#define ROW_7       	0x00FF000000000000
#define ROW_2       	0x000000000000FF00
#define BOTTOM_ROW    	0x00000000000000FF

namespace cengine
{
	enum Direction {
		UP,
		UP_RIGHT,
		RIGHT,
		DOWN_RIGHT,
		DOWN,
		DOWN_LEFT,
		LEFT,
		UP_LEFT
	};

	class BoardUtil
	{
		public:
			static uint64_t shift_piece(const uint64_t piece, const Direction direction);
	};
}

#endif
