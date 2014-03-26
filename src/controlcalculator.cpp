#include "controlcalculator.h"
#include "board.h"

namespace cengine
{
	uint64_t ControlCalculator::calculate_white_controlzone_for(const Board& board) const
	{
		return calculate_controlzone_for(board, Color::WHITE);
	}

	uint64_t ControlCalculator::calculate_black_controlzone_for(const Board& board) const
	{
		return calculate_controlzone_for(board, Color::BLACK);
	}

	uint64_t ControlCalculator::calculate_controlzone_for(const Board&  board, Color color) const
	{
		uint64_t control(0);

		control |= get_pawn_controlzone_for(board, color);
		control |= get_rook_controlzone_for(board, color);
		control |= get_knight_controlzone_for(board, color);
		control |= get_bishop_controlzone_for(board, color);
		control |= get_queen_controlzone_for(board, color);
		control |= get_king_controlzone_for(board, color);

		return control;
	}

	uint64_t ControlCalculator::get_pawn_controlzone_for(const Board& board, Color color) const
	{
		uint64_t pawns = color == Color::WHITE ? board.get_pieces_for(WHITE_PAWNS) : board.get_pieces_for(BLACK_PAWNS);
		uint64_t end_row = color == Color::WHITE ? TOP_ROW : BOTTOM_ROW;
		uint64_t control = 0;

		while (pawns != 0) {

			uint64_t pawn = (pawns & (pawns-1)) ^ pawns;
			pawns &= pawns-1;

			if((end_row & pawn) != 0)
			{
				continue;
			}

			if ((LEFT_COL & pawn) == 0) {
				control |= (color == Color::WHITE ? (pawn << 7) : (pawn >> 9) );
			}
			if((RIGHT_COL & pawn) == 0) {
				control |= (color == Color::WHITE ? (pawn << 9) : (pawn >> 7) );
			}

		}
		return control;
	}

	uint64_t ControlCalculator::get_rook_controlzone_for(const Board& board, Color color) const
	{
		return 0;
	}

	uint64_t ControlCalculator::get_knight_controlzone_for(const Board& board, Color color) const
	{
		return 0;
	}

	uint64_t ControlCalculator::get_bishop_controlzone_for(const Board& board, Color color) const
	{
		return 0;
	}

	uint64_t ControlCalculator::get_queen_controlzone_for(const Board& board, Color color) const
	{
		return 0;
	}

	uint64_t ControlCalculator::get_king_controlzone_for(const Board& board, Color color) const
	{
		return 0;
	}
}
