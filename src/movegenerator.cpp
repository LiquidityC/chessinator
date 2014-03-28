#include <cstdio>

#include "movegenerator.h"
#include "boardutil.h"
#include "move.h"

namespace cengine
{
	void MoveGenerator::calculate_moves_for(const Board& b)
	{
		possible_moves.clear();

		if (b.get_pieces_for(BLACK_KING) == 0
				|| b.get_pieces_for(WHITE_KING) == 0)
		{
			return;
		}

		// Fill the local vector
		calculate_pawn_moves_for(b);
		calculate_rook_moves_for(b);
		calculate_knight_moves_for(b);
		calculate_bishop_moves_for(b);
		calculate_queen_moves_for(b);
		calculate_king_moves_for(b);
		calculate_castling_moves(b);
	}

	void MoveGenerator::calculate_pawn_moves_for(const Board& b)
	{
		uint64_t pawns = b.is_whites_turn() ? b.get_pieces_for(WHITE_PAWNS) : b.get_pieces_for(BLACK_PAWNS);
		Unit enemyPieces = b.is_whites_turn() ? ALL_BLACK_PIECES : ALL_WHITE_PIECES;
		uint64_t allPieces = b.get_pieces_for(ALL_WHITE_PIECES) | b.get_pieces_for(ALL_BLACK_PIECES);

		uint64_t end_row = b.is_whites_turn() ? TOP_ROW : BOTTOM_ROW;
		uint64_t start_row = b.is_whites_turn() ? ROW_2 : ROW_7;

		while(pawns != 0)
		{
			uint64_t pawn = (pawns & (pawns-1)) ^ pawns;
			pawns &= pawns-1;
			// for each pawn
			if((end_row & pawn) != 0)
			{
				continue;
			}

			bool startPosition = (pawn & start_row) != 0;

			uint64_t destination = b.is_whites_turn() ? pawn << 8 : pawn >> 8;

			bool oneStepFree = (destination & allPieces) == 0;

			// One step forward
			if(oneStepFree)
			{
				add_move(b, pawn, destination);
			}

			// Two step forward
			if(oneStepFree && startPosition)
			{
				destination = b.is_whites_turn() ? pawn << 16 : pawn >> 16;
				bool twoStepFree = (destination & allPieces) == 0;
				if(twoStepFree)
				{
					add_move(b, pawn, destination);
				}
			}

			// Attack left
			if((LEFT_COL & pawn) == 0)
			{
				destination = b.is_whites_turn() ? pawn << 7 : pawn >> 9;
				if((destination & b.get_pieces_for(enemyPieces)) != 0)
				{
					add_move(b, pawn, destination);
				}
			}

			// Attack right
			if((RIGHT_COL & pawn) == 0)
			{
				destination = b.is_whites_turn() ? pawn << 9 : pawn >> 7;
				if((destination & b.get_pieces_for(enemyPieces)) != 0)
				{
					add_move(b, pawn, destination);
				}
			}
		}
	}

	void MoveGenerator::calculate_rook_moves_for(const Board& b)
	{
		uint64_t rooks = b.is_whites_turn() ? b.get_pieces_for(WHITE_ROOKS) : b.get_pieces_for(BLACK_ROOKS);

		while(rooks != 0)
		{
			uint64_t rook = (rooks & (rooks-1)) ^ rooks;
			rooks &= rooks-1;

			calculate_direction_moves(b, rook, UP);
			calculate_direction_moves(b, rook, RIGHT);
			calculate_direction_moves(b, rook, DOWN);
			calculate_direction_moves(b, rook, LEFT);
		}
	}

	void MoveGenerator::calculate_knight_moves_for(const Board& b)
	{
		Unit friendly_pieces = ALL_WHITE_PIECES;
		uint64_t knights = b.get_pieces_for(WHITE_KNIGHTS);
		if (!b.is_whites_turn()) {
			friendly_pieces = ALL_BLACK_PIECES;
			knights = b.get_pieces_for(BLACK_KNIGHTS);
		}

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
				if ((b.get_pieces_for(friendly_pieces) & knight<<15) == 0 && (!on_top_row && !on_row_7)) {
					add_move(b, knight, knight<<15);
				}
				if ((b.get_pieces_for(friendly_pieces) & knight>>17) == 0 && (!on_bottom_row && !on_row_2)) {
					add_move(b, knight, knight>>17);
				}
			}
			if ( !on_left_col && !on_col_b ) {
				if ((b.get_pieces_for(friendly_pieces) & knight<<6) == 0 && !on_top_row) {
					add_move(b, knight, knight<<6);
				}
				if ((b.get_pieces_for(friendly_pieces) & knight>>10) == 0 && !on_bottom_row) {
					add_move(b, knight, knight>>10);
				}
			}
			if ( !on_right_col ) {
				if ((b.get_pieces_for(friendly_pieces) & knight<<17) == 0 && (!on_top_row && !on_row_7)) {
					add_move(b, knight, knight<<17);
				}
				if ((b.get_pieces_for(friendly_pieces) & knight>>15) == 0 && (!on_bottom_row && !on_row_2)) {
					add_move(b, knight, knight>>15);
				}
			}
			if ( !on_right_col && !on_col_g ) {
				if ((b.get_pieces_for(friendly_pieces) & knight<<10) == 0 && !on_top_row) {
					add_move(b, knight, knight<<10);
				}
				if ((b.get_pieces_for(friendly_pieces) & knight>>6) == 0 && !on_bottom_row) {
					add_move(b, knight, knight>>6);
				}
			}
		}
	}

	void MoveGenerator::calculate_bishop_moves_for(const Board& b)
	{
		uint64_t bishops = b.is_whites_turn() ? b.get_pieces_for(WHITE_BISHOPS) : b.get_pieces_for(BLACK_BISHOPS);

		while(bishops != 0)
		{
			uint64_t bishop = (bishops & (bishops-1)) ^ bishops;
			bishops &= bishops-1;

			calculate_direction_moves(b, bishop, UP_RIGHT);
			calculate_direction_moves(b, bishop, DOWN_RIGHT);
			calculate_direction_moves(b, bishop, DOWN_LEFT);
			calculate_direction_moves(b, bishop, UP_LEFT);
		}
	}

	void MoveGenerator::calculate_queen_moves_for(const Board& b)
	{
		uint64_t queens = b.is_whites_turn() ? b.get_pieces_for(WHITE_QUEEN) : b.get_pieces_for(BLACK_QUEEN);

		while(queens != 0)
		{
			uint64_t queen = (queens & (queens-1)) ^ queens;
			queens &= queens-1;

			calculate_direction_moves(b, queen, UP);
			calculate_direction_moves(b, queen, UP_RIGHT);
			calculate_direction_moves(b, queen, RIGHT);
			calculate_direction_moves(b, queen, DOWN_RIGHT);
			calculate_direction_moves(b, queen, DOWN);
			calculate_direction_moves(b, queen, DOWN_LEFT);
			calculate_direction_moves(b, queen, LEFT);
			calculate_direction_moves(b, queen, UP_LEFT);
		}
	}

	void MoveGenerator::calculate_king_moves_for(const Board& b)
	{
		uint64_t king = b.is_whites_turn() ? b.get_pieces_for(WHITE_KING) : b.get_pieces_for(BLACK_KING);

		if(king == 0) {
			return;
		}

		bool on_top_row = (king & TOP_ROW) != 0;
		bool on_bottom_row = (king & BOTTOM_ROW) != 0;
		bool on_left_col = (king & LEFT_COL) != 0;
		bool on_right_col = (king & RIGHT_COL) != 0;

		uint64_t friend_pieces = b.is_whites_turn() ? b.get_pieces_for(ALL_WHITE_PIECES) : b.get_pieces_for(ALL_BLACK_PIECES);

		uint64_t destination;

		if(!on_left_col) {
			destination = BoardUtil::shift_piece(king, LEFT);
			if((destination & friend_pieces) == 0 ) {
				add_move(b, king, destination);
			}
			if(!on_top_row) {
				destination = BoardUtil::shift_piece(king, UP_LEFT);
				if((destination & friend_pieces) == 0 ) {
					add_move(b, king, destination);
				}
			}
			if(!on_bottom_row) {
				destination = BoardUtil::shift_piece(king, DOWN_LEFT);
				if((destination & friend_pieces) == 0 ) {
					add_move(b, king, destination);
				}
			}
		}
		if (!on_right_col) {
			destination = BoardUtil::shift_piece(king, RIGHT);
			if((destination & friend_pieces) == 0 ) {
				add_move(b, king, destination);
			}
			if(!on_top_row) {
				destination = BoardUtil::shift_piece(king, UP_RIGHT);
				if((destination & friend_pieces) == 0 ) {
					add_move(b, king, destination);
				}
			}
			if(!on_bottom_row) {
				destination = BoardUtil::shift_piece(king, DOWN_RIGHT);
				if((destination & friend_pieces) == 0 ) {
					add_move(b, king, destination);
				}
			}
		}

		if(!on_top_row) {
			destination = BoardUtil::shift_piece(king, UP);
			if((destination & friend_pieces) == 0 ) {
				add_move(b, king, destination);
			}
		}

		if(!on_bottom_row) {
			destination = BoardUtil::shift_piece(king, DOWN);
			if((destination & friend_pieces) == 0 ) {
				add_move(b, king, destination);
			}
		}
	}

	void MoveGenerator::calculate_castling_moves(const Board& b)
	{
		uint64_t long_block = 0xE;
		uint64_t short_block = 0x60;

		bool long_castling_available = b.is_white_long_castling_available();
		bool short_castling_available = b.is_white_short_castling_available();

		uint64_t castle_from = 0x10;
		uint64_t short_castle_to = 0x40;
		uint64_t long_castle_to = 0x4;

		if (!b.is_whites_turn()) {
			long_block <<= 56;
			short_block <<= 56;

			long_castling_available = b.is_black_long_castling_available();
			short_castling_available = b.is_black_short_castling_available();

			castle_from <<= 56;
			long_castle_to <<= 56;
			short_castle_to <<= 56;
		}

		bool black_pieces_blocking_long = (b.get_pieces_for(ALL_BLACK_PIECES) & long_block) != 0;
		bool black_pieces_blocking_short = (b.get_pieces_for(ALL_BLACK_PIECES) & short_block) != 0;
		bool white_pieces_blocking_long = (b.get_pieces_for(ALL_WHITE_PIECES) & long_block) != 0;
		bool white_pieces_blocking_short = (b.get_pieces_for(ALL_WHITE_PIECES) & short_block) != 0;

		if ( !black_pieces_blocking_long && !white_pieces_blocking_long && long_castling_available) {
			add_move(b, castle_from, long_castle_to);
		}
		if ( !black_pieces_blocking_short && !white_pieces_blocking_short && short_castling_available) {
			add_move(b, castle_from, short_castle_to);
		}
	}

	void MoveGenerator::calculate_direction_moves(const Board& board, const uint64_t piece, const Direction direction)
	{
		uint64_t position = piece;
		Unit enemyPieces = board.is_whites_turn() ? ALL_BLACK_PIECES : ALL_WHITE_PIECES;
		Unit friendPieces = board.is_whites_turn() ? ALL_WHITE_PIECES : ALL_BLACK_PIECES;

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

		while((endSquares & position) == 0)
		{
			position = BoardUtil::shift_piece(position, direction);

			if((position & board.get_pieces_for(enemyPieces)) != 0)
			{
				add_move(board, piece, position);
				break;
			}
			if((position & board.get_pieces_for(friendPieces)) != 0)
			{
				break;
			}
			add_move(board, piece, position);
		}
	}

	size_t MoveGenerator::move_count()
	{
		return possible_moves.size();
	}

	void MoveGenerator::add_move(const Board& board, uint64_t from, uint64_t to)
	{
		Board new_board(board);
		Move m(from, to);

		new_board.perform_move(m);

		bool moved_into_check = false;
		if (new_board.is_whites_turn()) {
			moved_into_check = new_board.is_black_in_check();
		} else {
			moved_into_check = new_board.is_white_in_check();
		}

		if(!moved_into_check && ( !attack_only || new_board.is_piece_taken())) {
			possible_moves.push_back(new_board);
		}
	}
}
