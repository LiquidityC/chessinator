#include <cstdio>

#include "movegenerator.h"
#include "move.h"
#include "boardutil.h"

#define WHITE_SQUARES 	0x55AA55AA55AA55AA
#define BLACK_SQUARES 	0xAA55AA55AA55AA55

#define LEFT_COL     	0x0101010101010101
#define COL_B			0x0202020202020202
#define COL_G			0x4040404040404040
#define RIGHT_COL      	0x8080808080808080

#define TOP_ROW       	0xFF00000000000000
#define ROW_7       	0x00FF000000000000
#define ROW_2       	0x000000000000FF00
#define BOTTOM_ROW    	0x00000000000000FF

namespace cengine
{
	void MoveGenerator::calculate_moves_for(const Board& b)
	{
		possible_moves.clear();

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
		uint64_t pawns = b.whites_turn ? b.pieces[WHITE_PAWNS] : b.pieces[BLACK_PAWNS];
		Units enemyPieces = b.whites_turn ? ALL_BLACK_PIECES : ALL_WHITE_PIECES;
		uint64_t allPieces = b.pieces[ALL_WHITE_PIECES] | b.pieces[ALL_BLACK_PIECES];

		uint64_t end_row = b.whites_turn ? TOP_ROW : BOTTOM_ROW;
		uint64_t start_row = b.whites_turn ? ROW_2 : ROW_7;

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

			uint64_t destination = b.whites_turn ? pawn << 8 : pawn >> 8;

			bool oneStepFree = (destination & allPieces) == 0;

			// One step forward
			if(oneStepFree)
			{
				add_move(b, pawn, destination);
			}

			// Two step forward
			if(oneStepFree && startPosition)
			{
				destination = b.whites_turn ? pawn << 16 : pawn >> 16;
				bool twoStepFree = (destination & allPieces) == 0;
				if(twoStepFree)
				{
					add_move(b, pawn, destination);
				}
			}

			// Attack left
			if((LEFT_COL & pawn) == 0)
			{
				destination = b.whites_turn ? pawn << 7 : pawn >> 9;
				if((destination & b.pieces[enemyPieces]) != 0)
				{
					add_move(b, pawn, destination);
				}
			}

			// Attack right
			if((RIGHT_COL & pawn) == 0)
			{
				destination = b.whites_turn ? pawn << 9 : pawn >> 7;
				if((destination & b.pieces[enemyPieces]) != 0)
				{
					add_move(b, pawn, destination);
				}
			}
		}
	}

	void MoveGenerator::calculate_rook_moves_for(const Board& b)
	{
		uint64_t rooks = b.whites_turn ? b.pieces[WHITE_ROOKS] : b.pieces[BLACK_ROOKS];

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
		Units friendly_pieces = ALL_WHITE_PIECES;
		uint64_t knights = b.pieces[WHITE_KNIGHTS];
		if (!b.whites_turn) {
			friendly_pieces = ALL_BLACK_PIECES;
			knights = b.pieces[BLACK_KNIGHTS];
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
				if ((b.pieces[friendly_pieces] & knight<<15) == 0 && (!on_top_row && !on_row_7)) {
					add_move(b, knight, knight<<15);
				}
				if ((b.pieces[friendly_pieces] & knight>>17) == 0 && (!on_bottom_row && !on_row_2)) {
					add_move(b, knight, knight>>17);
				}
			}
			if ( !on_left_col && !on_col_b ) {
				if ((b.pieces[friendly_pieces] & knight<<6) == 0 && !on_top_row) {
					add_move(b, knight, knight<<6);
				}
				if ((b.pieces[friendly_pieces] & knight>>10) == 0 && !on_bottom_row) {
					add_move(b, knight, knight>>10);
				}
			}
			if ( !on_right_col ) {
				if ((b.pieces[friendly_pieces] & knight<<17) == 0 && (!on_top_row && !on_row_7)) {
					add_move(b, knight, knight<<17);
				}
				if ((b.pieces[friendly_pieces] & knight>>15) == 0 && (!on_bottom_row && !on_row_2)) {
					add_move(b, knight, knight>>15);
				}
			}
			if ( !on_right_col && !on_col_g ) {
				if ((b.pieces[friendly_pieces] & knight<<10) == 0 && !on_top_row) {
					add_move(b, knight, knight<<10);
				}
				if ((b.pieces[friendly_pieces] & knight>>6) == 0 && !on_bottom_row) {
					add_move(b, knight, knight>>6);
				}
			}
		}
	}

	void MoveGenerator::calculate_bishop_moves_for(const Board& b)
	{
		uint64_t bishops = b.whites_turn ? b.pieces[WHITE_BISHOPS] : b.pieces[BLACK_BISHOPS];

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
		uint64_t queens = b.whites_turn ? b.pieces[WHITE_QUEEN] : b.pieces[BLACK_QUEEN];

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
		uint64_t king = b.pieces[WHITE_KING];
		if (!b.whites_turn) {
			king = b.pieces[BLACK_KING];
		}

		bool on_top_row = (king & TOP_ROW) != 0;
		bool on_bottom_row = (king & BOTTOM_ROW) != 0;
		bool on_left_col = (king & LEFT_COL) != 0;
		bool on_right_col = (king & RIGHT_COL) != 0;

		if (!on_left_col) {
			if ((king>>1 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0) {
				add_move(b, king, king>>1);
			}
			if ((king<<7 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0 && !on_top_row) {
				add_move(b, king, king<<7);
			}
			if ((king>>9 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0 && !on_bottom_row) {
				add_move(b, king, king<<9);
			}
		}
		if (!on_right_col) {
			if ((king<<1 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0) {
				add_move(b, king, king>>1);
			}
			if ((king<<9 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0 && !on_top_row) {
				add_move(b, king, king<<9);
			}
			if ((king>>7 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0 && !on_bottom_row) {
				add_move(b, king, king>>7);
			}
		}
		if (!on_top_row) {
			if ((king<<8 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0) {
				add_move(b, king, king<<8);
			}
		}
		if (!on_bottom_row) {
			if ((king>>8 & b.pieces[ALL_WHITE_PIECES]) == 0 && (king>>1 & b.pieces[ALL_BLACK_PIECES]) == 0) {
				add_move(b, king, king>>8);
			}
		}
	}

	void MoveGenerator::calculate_castling_moves(const Board& b)
	{
		uint64_t long_block = 0xE;
		uint64_t short_block = 0x60;

		bool long_castling_available = b.white_long_castling_available;
		bool short_castling_available = b.white_short_castling_available;

		uint64_t castle_from = 0x10;
		uint64_t short_castle_to = 0x80;
		uint64_t long_castle_to = 0x4;

		if (!b.whites_turn) {
			long_block <<= 56;
			short_block <<= 56;

			long_castling_available = b.black_long_castling_available;
			short_castling_available = b.black_short_castling_available;

			castle_from <<= 56;
			long_castle_to <<= 56;
			short_castle_to <<= 56;
		}

		bool black_pieces_blocking_long = (b.pieces[ALL_BLACK_PIECES] & long_block) != 0;
		bool black_pieces_blocking_short = (b.pieces[ALL_BLACK_PIECES] & short_block) != 0;
		bool white_pieces_blocking_long = (b.pieces[ALL_WHITE_PIECES] & long_block) != 0;
		bool white_pieces_blocking_short = (b.pieces[ALL_WHITE_PIECES] & short_block) != 0;

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
		Units enemyPieces = board.whites_turn ? ALL_BLACK_PIECES : ALL_WHITE_PIECES;
		Units friendPieces = board.whites_turn ? ALL_WHITE_PIECES : ALL_BLACK_PIECES;

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
			shift_piece(position, direction);

			if((position & board.pieces[enemyPieces]) != 0)
			{
				add_move(board, piece, position);
				break;
			}
			if((position & board.pieces[friendPieces]) != 0)
			{
				break;
			}
			add_move(board, piece, position);
		}
	}

	void MoveGenerator::shift_piece(uint64_t& piece, const Direction direction)
	{
		switch(direction)
		{
			case UP:
				piece <<= 8;
				break;
			case UP_RIGHT:
				piece <<= 9;
				break;
			case RIGHT:
				piece <<= 1;
				break;
			case DOWN_RIGHT:
				piece >>= 7;
				break;
			case DOWN:
				piece >>= 8;
				break;
			case DOWN_LEFT:
				piece >>= 9;
				break;
			case LEFT:
				piece >>= 1;
				break;
			case UP_LEFT:
				piece <<= 7;
				break;
		}
	}

	size_t MoveGenerator::move_count()
	{
		return possible_moves.size();
	}

	void MoveGenerator::add_move(const Board& board, uint64_t from, uint64_t to)
	{
		Board new_board = board;
		Move m(from, to);

		BoardUtil::perform_move(m, new_board);

		possible_moves.push_back(new_board);
	}
}
