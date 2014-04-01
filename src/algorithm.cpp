#include <climits>
#include <iostream>
#include "algorithm.h"
#include "board.h"
#include "evaluator.h"
#include "movegenerator.h"
#include "move.h"

namespace cengine
{

	Move* Algorithm::get_move(const Board& board)
	{
		MoveGenerator mgen;

		mgen.calculate_moves_for(board);

		if (mgen.begin() == mgen.end()) {
			return NULL;
		}

		int max = -INT_MAX;
		Move* best_move = NULL;

		for (auto it = mgen.begin(); it != mgen.end(); it++) {
			int value = alphabeta(*it, 3, -INT_MAX, INT_MAX, false);
			if(max <= value) {
				max = value;

				if(best_move != NULL) {
					delete best_move;
				}
				best_move = new Move((*it).get_last_move());
			}
		}

		return best_move;
	}

	int Algorithm::alphabeta(const Board& board, unsigned int depth, int a, int b, bool max_player)
	{
		if (depth == 0) {
			if(board.is_piece_taken()) {
				return quiescenceSearch(board, 3, a, b, max_player);
			} else {
				return Evaluator::evaluate(board, max_player);
			}
		}

		MoveGenerator mgen;
		mgen.calculate_moves_for(board);

		if (mgen.begin() == mgen.end()) {
			return Evaluator::evaluate(board, max_player, true);
		}

		if (max_player) {
			for (auto it = mgen.begin(); it != mgen.end(); it++) {
				a = std::max(a, alphabeta(*it, depth - 1, a, b, false));
				if (b <= a) {
					break;
				}
			}
			return a;
		} else {
			for (auto it = mgen.begin(); it != mgen.end(); it++) {
				b = std::min(b, alphabeta(*it, depth - 1, a, b, true));
				if (b <= a) {
					break;
				}
			}
			return b;
		}
	}

	int Algorithm::quiescenceSearch(const Board& board, unsigned int depth, int a, int b, bool max_player)
	{
		if(depth == 0) {
			return Evaluator::evaluate(board, max_player);
		}

		MoveGenerator mgen;
		mgen.set_attack_only(true);
		mgen.calculate_moves_for(board);

		if (mgen.begin() == mgen.end()) {
			return Evaluator::evaluate(board, max_player);
		}

		if (max_player) {
			for (auto it = mgen.begin(); it != mgen.end(); it++) {
				a = std::max(a, quiescenceSearch(*it, depth - 1, a, b, false));
				if (b <= a) {
					break;
				}
			}
			return a;
		} else {
			for (auto it = mgen.begin(); it != mgen.end(); it++) {
				b = std::min(b, quiescenceSearch(*it, depth - 1, a, b, true));
				if (b <= a) {
					break;
				}
			}
			return b;
		}
	}
}
