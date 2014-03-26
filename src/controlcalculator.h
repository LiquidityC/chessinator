#ifndef _CONTROL_CALCULATOR_H
#define _CONTROL_CALCULATOR_H

#include <cstdint>
#include "boardutil.h"

namespace cengine
{
	class Board;

	enum Color {
		WHITE,
		BLACK
	};

	class ControlCalculator
	{
		public:

			uint64_t calculate_white_controlzone_for(const Board&) const;

			uint64_t calculate_black_controlzone_for(const Board&) const;

		private:

			uint64_t calculate_controlzone_for(const Board&, Color) const;

			uint64_t get_pawn_controlzone_for(const Board&, Color) const;
			uint64_t get_rook_controlzone_for(const Board&, Color) const;
			uint64_t get_knight_controlzone_for(const Board&, Color) const;
			uint64_t get_bishop_controlzone_for(const Board&, Color) const;
			uint64_t get_queen_controlzone_for(const Board&, Color) const;
			uint64_t get_king_controlzone_for(const Board&, Color) const;

			uint64_t calculate_direction_control(const Board&, const uint64_t piece, Direction) const;
	};
}

#endif
