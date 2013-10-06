#include "alphabeta.h"
#include "board.h"

namespace cengine
{
	long AlphaBeta::run(Board board, unsigned int depth, long a, long b, bool maxPlayer)
	{
		if (depth == 0 /* || is_leaf_node */) {
			// return score_of(board);
		}

		if (maxPlayer) {
			/* for (each possible move of board) {
			 * 		a = max(a, alphabeta(newBoard, depth - 1, a, b, false));
			 * 		if (a <= b) {
			 * 				break;
			 * 		}
			 * 		return a;
			 * } */
		} else {
			/* for (each possible move of board) {
			 * 		b = min(b, alphabeta(newBoard, depth - 1, a, b, false));
			 * 		if (b <= a) {
			 * 				break;
			 * 		}
			 * 		return b;
			 * } */
		}

		return 0;
	}
}
