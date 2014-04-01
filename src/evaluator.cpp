#include <climits>

#include "evaluator.h"
#include "board.h"

#define PAWN_VALUE		100
#define KNIGHT_VALUE	320
#define BISHOP_VALUE	325
#define ROOK_VALUE		500
#define QUEEN_VALUE		975
#define KING_VALUE		32767

#define count_bits(pieces) (__builtin_popcount(pieces))

namespace cengine
{
	int Evaluator::evaluate(const Board& b, bool max_player, bool no_children)
	{
		bool playing_white = b.is_whites_turn() == max_player;
		if (no_children) {
			if (playing_white && b.is_black_in_check()) {
				return INT_MAX;
			} else if (!playing_white && b.is_white_in_check()) {
				return INT_MAX;
			} else {
				return -INT_MAX;
			}
		}

		int material_score = 
			+ PAWN_VALUE * (count_pieces(b, WHITE_PAWNS) - count_pieces(b, BLACK_PAWNS))
			+ KNIGHT_VALUE * (count_pieces(b, WHITE_KNIGHTS) - count_pieces(b, BLACK_KNIGHTS))
			+ BISHOP_VALUE * (count_pieces(b, WHITE_BISHOPS) - count_pieces(b, BLACK_BISHOPS))
			+ ROOK_VALUE * (count_pieces(b, WHITE_ROOKS) - count_pieces(b, BLACK_ROOKS))
			+ QUEEN_VALUE * (count_pieces(b, WHITE_QUEEN) - count_pieces(b, BLACK_QUEEN))
			+ KING_VALUE * (count_pieces(b, WHITE_KING) - count_pieces(b, BLACK_KING));

		int total_score = material_score;

		if(playing_white) {
			return total_score;
		} else {
			return total_score * -1;
		}
	}

	int Evaluator::count_pieces(const Board& b, Unit u)
	{
		uint64_t i = b.get_pieces_for(u);
		return count_bits(i);
	}
}
