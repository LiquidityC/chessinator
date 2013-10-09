#include <cstdio>

#include "movegenerator.h"
#include "move.h"
#include "boardutil.h"

#define WHITE_SQUARES 	0xAA55AA55AA55AA55
#define BLACK_SQUARES 	0x55AA55AA55AA55AA

#define LEFT_COL      	0x8080808080808080
#define COL_B			0x0202020202020202
#define COL_G			0x4040404040404040
#define RIGHT_COL     	0x0101010101010101

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
	}

	void MoveGenerator::calculate_pawn_moves_for(const Board& b)
	{
		uint64_t pawns = b.pieces[WHITE_PAWNS];

		while(pawns != 0)
		{
			uint64_t pawn = (pawns & (pawns-1)) ^ pawns;
			pawns &= pawns-1;
			// for each pawn
			if((TOP_ROW & pawn) != 0)
			{
				continue;
			}

			uint64_t destination;

			bool firstPosition = (pawn & 0xFF00) != 0;
			uint64_t allPieces = b.pieces[ALL_WHITE_PIECES] | b.pieces[ALL_BLACK_PIECES];

			bool oneStepFree = ((pawn << 8) & allPieces) == 0;

			// One step forward
			if(oneStepFree)
			{
				destination = pawn << 8;
				add_move(b, pawn, destination);
			}

			// Two step forward
			if(oneStepFree && firstPosition)
			{
				destination = pawn << 16;
				bool twoStepFree = (destination & allPieces) == 0;
				if(twoStepFree)
				{
					add_move(b, pawn, destination);
				}
			}

			// Attack left
			if((LEFT_COL & pawn) == 0)
			{
				destination = pawn << 9;
				if((destination & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					add_move(b, pawn, destination);
				}
			}

			// Attack right
			if((RIGHT_COL & pawn) == 0)
			{
				destination = pawn << 7;
				if((destination & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					add_move(b, pawn, destination);
				}
			}
		}
	}

	void MoveGenerator::calculate_rook_moves_for(const Board& b)
	{
		// XXX: Totally untested, just some ideas.
		// Some copied from above, refactor and test soon.
		uint64_t rooks = b.pieces[WHITE_ROOKS];

		while(rooks != 0)
		{
			uint64_t rook = (rooks & (rooks-1)) ^ rooks;
			rooks &= rooks-1;

			uint64_t position = rook;

			// Left
			while((LEFT_COL & position) == 0)
			{
				position <<= 1;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					// Attack
					add_move(b, rook, position);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					// Blocked
					break;
				}
				add_move(b, rook, position);
			}

			position = rook;
			while((RIGHT_COL & position) == 0)
			{
				position >>= 1;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					add_move(b, rook, position);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					break;
				}
				add_move(b, rook, position);
			}

			position = rook;
			while((TOP_ROW & position) == 0)
			{
				position <<= 8;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					add_move(b, rook, position);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					break;
				}
				add_move(b, rook, position);
			}

			position = rook;
			while((BOTTOM_ROW & position) == 0)
			{
				position >>= 8;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					add_move(b, rook, position);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					break;
				}
				add_move(b, rook, position);
			}
		}
	}

	void MoveGenerator::calculate_knight_moves_for(const Board& b)
	{
		// Shifts: 6, 10, 15, 17
		uint64_t knights = b.pieces[WHITE_ROOKS];

		while(knights != 0)
		{
			uint64_t knight = (knights & (knights-1)) ^ knights;
			knights &= knights-1;

			if ( (knight & LEFT_COL) == 0) {
				if ((b.pieces[ALL_WHITE_PIECES] & knight<<15) == 0 && (knight & TOP_ROW & ROW_7) == 0) {
					add_move(b, knight, knight<<15);
				}
				if ((b.pieces[ALL_WHITE_PIECES] & knight>>17) == 0 && (knight & BOTTOM_ROW & ROW_2) == 0) {
					add_move(b, knight, knight>>17);
				}
			}
			if ( (knight & LEFT_COL & COL_B) == 0) {
				if ((b.pieces[ALL_WHITE_PIECES] & knight<<6) == 0 && (knight & TOP_ROW) == 0) {
					add_move(b, knight, knight<<6);
				}
				if ((b.pieces[ALL_WHITE_PIECES] & knight>>10) == 0 && (knight & BOTTOM_ROW) == 0) {
					add_move(b, knight, knight>>10);
				}
			}
			if ( (knight & RIGHT_COL) == 0) {
				if ((b.pieces[ALL_WHITE_PIECES] & knight<<17) == 0 && (knight & TOP_ROW & ROW_7) == 0) {
					add_move(b, knight, knight<<17);
				}
				if ((b.pieces[ALL_WHITE_PIECES] & knight>>15) == 0 && (knight & BOTTOM_ROW & ROW_2) == 0) {
					add_move(b, knight, knight>>15);
				}
			}
			if ( (knight & RIGHT_COL & COL_G) == 0) {
				if ((b.pieces[ALL_WHITE_PIECES] & knight<<10) == 0 && (knight & TOP_ROW) == 0) {
					add_move(b, knight, knight<<10);
				}
				if ((b.pieces[ALL_WHITE_PIECES] & knight>>6) == 0 && (knight & BOTTOM_ROW) == 0) {
					add_move(b, knight, knight>>6);
				}
			}
		}

	}

	void MoveGenerator::calculate_bishop_moves_for(const Board& b)
	{
		// TODO: Implement me
	}

	void MoveGenerator::calculate_queen_moves_for(const Board& b)
	{
		// TODO: Implement me
	}

	void MoveGenerator::calculate_king_moves_for(const Board& b)
	{
		// TODO: Implement me
	}

	void MoveGenerator::add_move(const Board& board, uint64_t from, uint64_t to)
	{
		Board new_board = board;
		Move m(from, to);

		BoardUtil::perform_move(m, new_board);

		possible_moves.push_back(new_board);
	}
}
