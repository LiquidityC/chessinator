#include "movegenerator.h"
#include <cstdio>

#define WHITE_SQUARES 0xAA55AA55AA55AA55
#define BLACK_SQUARES 0x55AA55AA55AA55AA
#define LEFT_ROW      0x8080808080808080
#define RIGHT_ROW     0x0101010101010101
#define TOP_ROW       0xFF00000000000000
#define BOTTOM_ROW    0x00000000000000FF

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
				addMove(b, pawn, destination, WHITE_PAWNS);
			}

			// Two step forward
			if(oneStepFree && firstPosition)
			{
				destination = pawn << 16;
				bool twoStepFree = (destination & allPieces) == 0;
				if(twoStepFree)
				{
					addMove(b, pawn, destination, WHITE_PAWNS);
				}
			}

			// Attack left
			if((LEFT_ROW & pawn) == 0)
			{
				destination = pawn << 9;
				if((destination & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					addMove(b, pawn, destination, WHITE_PAWNS);
				}
			}

			// Attack right
			if((RIGHT_ROW & pawn) == 0)
			{
				destination = pawn << 7;
				if((destination & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					addMove(b, pawn, destination, WHITE_PAWNS);
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
			while((LEFT_ROW & position) == 0)
			{
				position <<= 1;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					// Attack
					addMove(b, rook, position, WHITE_ROOKS);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					// Blocked
					break;
				}
				addMove(b, rook, position, WHITE_ROOKS);
			}

			position = rook;
			while((RIGHT_ROW & position) == 0)
			{
				position >>= 1;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					addMove(b, rook, position, WHITE_ROOKS);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					break;
				}
				addMove(b, rook, position, WHITE_ROOKS);
			}

			position = rook;
			while((TOP_ROW & position) == 0)
			{
				position <<= 8;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					addMove(b, rook, position, WHITE_ROOKS);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					break;
				}
				addMove(b, rook, position, WHITE_ROOKS);
			}

			position = rook;
			while((BOTTOM_ROW & position) == 0)
			{
				position >>= 8;
				if((position & b.pieces[ALL_BLACK_PIECES]) != 0)
				{
					addMove(b, rook, position, WHITE_ROOKS);
					break;
				}
				if((position & b.pieces[ALL_WHITE_PIECES]) != 0)
				{
					break;
				}
				addMove(b, rook, position, WHITE_ROOKS);
			}
		}
	}

	void MoveGenerator::calculate_knight_moves_for(const Board& b)
	{
		// TODO: Implement me
		// Shifts: 6, 10, 15, 17
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

	void MoveGenerator::addMove(const Board& board, uint64_t from, uint64_t to, Units unit)
	{
		Board newBoard = board;
		newBoard.pieces[unit] = newBoard.pieces[unit] & ~from;
		for(int i = WHITE_PAWNS; i < PIECES_SIZE; i++)
		{
			newBoard.pieces[i] = newBoard.pieces[i] & ~to;
		}
		newBoard.pieces[unit] |= to;
		if(unit <= WHITE_KING)
		{
			newBoard.pieces[ALL_WHITE_PIECES] |= to;
		}
		else
		{
			newBoard.pieces[ALL_BLACK_PIECES] |= to;
		}

		possible_moves.push_back(newBoard);
	}
}
