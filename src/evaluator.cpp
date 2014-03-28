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

		int white_score = 0;
		white_score += PAWN_VALUE * count_pieces(b, WHITE_PAWNS);
		white_score += KNIGHT_VALUE * count_pieces(b, WHITE_KNIGHTS);
		white_score += BISHOP_VALUE * count_pieces(b, WHITE_BISHOPS);
		white_score += ROOK_VALUE * count_pieces(b, WHITE_ROOKS);
		white_score += QUEEN_VALUE * count_pieces(b, WHITE_QUEEN);
		white_score += KING_VALUE * count_pieces(b, WHITE_KING);
		white_score += 10 * count_bits(b.get_pieces_for(ALL_BLACK_PIECES) & b.get_white_control());

		white_score += b.is_black_in_check() ? 50 : 0;
		if(count_pieces(b, WHITE_BISHOPS) > 1) {
			white_score += 50;
		}

		int black_score = 0;
		black_score += PAWN_VALUE * count_pieces(b, BLACK_PAWNS);
		black_score += KNIGHT_VALUE * count_pieces(b, BLACK_KNIGHTS);
		black_score += BISHOP_VALUE * count_pieces(b, BLACK_BISHOPS);
		black_score += ROOK_VALUE * count_pieces(b, BLACK_ROOKS);
		black_score += QUEEN_VALUE * count_pieces(b, BLACK_QUEEN);
		black_score += KING_VALUE * count_pieces(b, BLACK_KING);
		black_score += 10 * count_bits(b.get_pieces_for(ALL_WHITE_PIECES) & b.get_black_control());

		black_score += b.is_white_in_check() ? 50 : 0;
		if(count_pieces(b, BLACK_BISHOPS) > 1) {
			black_score += 50;
		}

		if(playing_white) {
			return white_score - black_score;
		} else {
			return black_score - white_score;
		}
	}

	int Evaluator::count_pieces(const Board& b, Unit u)
	{
		uint64_t i = b.get_pieces_for(u);
		return count_bits(i);
	}
}
