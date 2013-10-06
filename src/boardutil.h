#ifndef _BOARD_UTIL_H
#define _BOARD_UTIL_H

#include <string>

#include "board.h"

namespace cengine
{
	class Move;

	class BoardUtil
	{
		public:

			Board create_board();

			void perform_move(Move&, Board&);

	};
}

#endif
