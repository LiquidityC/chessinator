#ifndef _BOARD_UTIL_H
#define _BOARD_UTIL_H

#include <string>
#include <fstream>

#include "board.h"

namespace cengine
{
	class Move;

	class BoardUtil
	{
		private:

			static Units get_target_for_move(uint64_t&, Board&);

			static void perform_regular_move(const Move&, Board&);

			static void perform_castling_move(const Move&, Board&);

			static void check_castling_impact(const Move&, Board&);

		public:

			static Board create_board();

			static Board create_board(std::ifstream&);

			static void print_board(std::ostream&, const Board&);

			static void perform_move(const Move&, Board&);
	};
}

#endif
