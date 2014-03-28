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
}
