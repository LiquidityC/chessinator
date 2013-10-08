#include "movegenerator.h"

#define WHITE_SQUARES 0xAA55AA55AA55AA55
#define BLACK_SQUARES 0x55AA55AA55AA55AA
#define LEFT_ROW 0x8080808080808080
#define RIGHT_ROW 0x0101010101010101

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

		while(pawns != 0) {
			uint64_t pawn = (pawns & (pawns-1)) ^ pawns;
			pawns &= pawns-1;
			// for each pawn

			uint64_t destination;

			bool firstPosition = (pawn & 0xFF00) != 0;
			uint64_t allPieces = b.pieces[ALL_WHITE_PIECES] | b.pieces[ALL_BLACK_PIECES];
			bool oneStepFree = ((pawn >> 8) & allPieces) == 0;

			// One step forward
			if(oneStepFree) {
				destination = pawn >> 8;
				// TODO: add move
			}

			// Two step forward
			if(oneStepFree && firstPosition) {
				destination = pawn >> 16;
				bool twoStepFree = (destination & allPieces) == 0;
				if(twoStepFree) {
					// TODO: add move
				}
			}

			// Attack left
			if((LEFT_ROW & pawn) == 0) {
				destination = pawn << 9;
				if((destination & b.pieces[ALL_BLACK_PIECES]) != 0) {
					// TODO: add move
				}
			}

			// Attack right
			if((RIGHT_ROW & pawn) == 0) {
				destination = pawn << 7;
				if((destination & b.pieces[ALL_BLACK_PIECES]) != 0) {
					// TODO: add move
				}
			}
		}
	}

	void MoveGenerator::calculate_rook_moves_for(const Board& b)
	{
		// TODO: Implement me
		// Shifts: 6, 10, 15, 17
	}

	void MoveGenerator::calculate_knight_moves_for(const Board& b)
	{
		// TODO: Implement me
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
}
