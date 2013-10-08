#ifndef _BOARD_UTIL_H
#define _BOARD_UTIL_H

#include <string>

#include "board.h"

namespace cengine
{
	class Move;

	class BoardUtil
	{
		private:

			static uint64_t& get_target_for_move(uint64_t&, Board&);

		public:

			static Board create_board();

			static void perform_move(Move&, Board&);

	};
}

#endif
