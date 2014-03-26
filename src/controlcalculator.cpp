#include "controlcalculator.h"
#include "board.h"
#include "boardutil.h"

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
		uint64_t rooks = color == Color::WHITE ? board.get_pieces_for(WHITE_ROOKS) : board.get_pieces_for(BLACK_ROOKS);
		uint64_t control = 0;

		while (rooks != 0) {

			uint64_t rook = (rooks & (rooks-1)) ^ rooks;
			rooks &= rooks-1;

			control |= calculate_direction_control(board, rook, Direction::UP);
			control |= calculate_direction_control(board, rook, Direction::DOWN);
			control |= calculate_direction_control(board, rook, Direction::LEFT);
			control |= calculate_direction_control(board, rook, Direction::RIGHT);
		}

		return control;
	}

	uint64_t ControlCalculator::get_knight_controlzone_for(const Board& board, Color color) const
	{
		uint64_t knights = color == Color::WHITE ? board.get_pieces_for(WHITE_KNIGHTS) : board.get_pieces_for(BLACK_KNIGHTS);
		uint64_t control = 0;

		while(knights != 0)
		{
			uint64_t knight = (knights & (knights-1)) ^ knights;
			knights &= knights-1;

			bool on_bottom_row = (knight & BOTTOM_ROW) != 0;
			bool on_row_2 = (knight & ROW_2) != 0;
			bool on_row_7 = (knight & ROW_7) != 0;
			bool on_top_row = (knight & TOP_ROW) != 0;

			bool on_left_col = (knight & LEFT_COL) != 0;
			bool on_col_b = (knight & COL_B) != 0;
			bool on_col_g = (knight & COL_G) != 0;
			bool on_right_col = (knight & RIGHT_COL) != 0;

			if ( !on_left_col ) {
				if (!on_top_row && !on_row_7) {
					control |= knight << 15;
				}
				if (!on_bottom_row && !on_row_2) {
					control |= knight >> 17;
				}
			}
			if ( !on_left_col && !on_col_b ) {
				if (!on_top_row) {
					control |= knight << 6;
				}
				if (!on_bottom_row) {
					control |= knight >> 10;
				}
			}
			if ( !on_right_col ) {
				if (!on_top_row && !on_row_7) {
					control |= knight << 17;
				}
				if (!on_bottom_row && !on_row_2) {
					control |= knight >> 15;
				}
			}
			if ( !on_right_col && !on_col_g ) {
				if (!on_top_row) {
					control |= knight << 10;
				}
				if (!on_bottom_row) {
					control |= knight >> 6;
				}
			}
		}
		return control;
	}

	uint64_t ControlCalculator::get_bishop_controlzone_for(const Board& board, Color color) const
	{
		uint64_t bishops = color == Color::WHITE ? board.get_pieces_for(WHITE_BISHOPS) : board.get_pieces_for(BLACK_BISHOPS);
		uint64_t control = 0;

		while (bishops != 0) {

			uint64_t bishop = (bishops & (bishops-1)) ^ bishops;
			bishops &= bishops-1;

			control |= calculate_direction_control(board, bishop, Direction::UP_LEFT);
			control |= calculate_direction_control(board, bishop, Direction::UP_RIGHT);
			control |= calculate_direction_control(board, bishop, Direction::DOWN_LEFT);
			control |= calculate_direction_control(board, bishop, Direction::DOWN_RIGHT);
		}

		return control;
	}

	uint64_t ControlCalculator::get_queen_controlzone_for(const Board& board, Color color) const
	{
		uint64_t queens = color == Color::WHITE ? board.get_pieces_for(WHITE_QUEEN) : board.get_pieces_for(BLACK_QUEEN);
		uint64_t control = 0;

		while (queens != 0) {

			uint64_t queen = (queens & (queens-1)) ^ queens;
			queens &= queens-1;

			control |= calculate_direction_control(board, queen, Direction::UP);
			control |= calculate_direction_control(board, queen, Direction::UP_RIGHT);
			control |= calculate_direction_control(board, queen, Direction::RIGHT);
			control |= calculate_direction_control(board, queen, Direction::DOWN_RIGHT);
			control |= calculate_direction_control(board, queen, Direction::DOWN);
			control |= calculate_direction_control(board, queen, Direction::DOWN_LEFT);
			control |= calculate_direction_control(board, queen, Direction::LEFT);
			control |= calculate_direction_control(board, queen, Direction::UP_LEFT);
		}

		return control;
	}

	uint64_t ControlCalculator::get_king_controlzone_for(const Board& board, Color color) const
	{
		uint64_t king = color == Color::WHITE ? board.get_pieces_for(WHITE_KING) : board.get_pieces_for(BLACK_KING);
		uint64_t control = 0;

		if ((king & TOP_ROW) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::UP);
		}
		if ((king & TOP_ROW) == 0 && (king & RIGHT_COL) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::UP_RIGHT);
		}
		if ((king & RIGHT_COL) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::RIGHT);
		}
		if ((king & BOTTOM_ROW) == 0 && (king & RIGHT_COL) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::DOWN_RIGHT);
		}
		if ((king & BOTTOM_ROW) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::DOWN);
		}
		if ((king & BOTTOM_ROW) == 0 && (king & LEFT_COL) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::DOWN_LEFT);
		}
		if ((king & LEFT_COL) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::LEFT);
		}
		if ((king & TOP_ROW) == 0 && (king & LEFT_COL) == 0) {
			control |= BoardUtil::shift_piece(king, Direction::UP_LEFT);
		}

		return control;
	}

	uint64_t ControlCalculator::calculate_direction_control(const Board& board, const uint64_t piece, Direction direction) const
	{
		uint64_t position = piece;
		uint64_t endSquares;

		switch(direction)
		{
			case UP:
				endSquares = TOP_ROW;
				break;
			case UP_RIGHT:
				endSquares = TOP_ROW | RIGHT_COL;
				break;
			case RIGHT:
				endSquares = RIGHT_COL;
				break;
			case DOWN_RIGHT:
				endSquares = RIGHT_COL | BOTTOM_ROW;
				break;
			case DOWN:
				endSquares = BOTTOM_ROW;
				break;
			case DOWN_LEFT:
				endSquares = BOTTOM_ROW | LEFT_COL;
				break;
			case LEFT:
				endSquares = LEFT_COL;
				break;
			case UP_LEFT:
				endSquares = LEFT_COL | TOP_ROW;
				break;
		}

		uint64_t all_pieces(0);
		all_pieces |= board.get_pieces_for(ALL_WHITE_PIECES);
		all_pieces |= board.get_pieces_for(ALL_BLACK_PIECES);

		uint64_t control(0);

		if ((endSquares & position) != 0) {
			return control;
		}

		while((endSquares & position) == 0) {
			position = BoardUtil::shift_piece(position, direction);
			control |= position;

			if((position & all_pieces) != 0) {
				break;
			}
		}

		// Add the final square
		control |= position;

		return control;
	}
}
