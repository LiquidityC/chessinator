#include <climits>
#include <iostream>
#include "algorithm.h"
#include "board.h"
#include "evaluator.h"
#include "movegenerator.h"
#include "move.h"

namespace cengine
{

	Move Algorithm::get_move(const Board& board)
	{
		m_generator.calculate_moves_for(board);
		int max = -INT_MAX;
		Move* best_move = NULL;

		for (auto it = m_generator.begin(); it != m_generator.end(); it++) {
			int value = alphabeta(*it, 1, -INT_MAX, INT_MAX, false);
			if(max < value) {
				max = value;
				if(best_move != NULL) {
					delete best_move;
				}
				best_move = new Move((*it).get_last_move());
			}
		}
		return *best_move;
	}


	int Algorithm::alphabeta(const Board& board, unsigned int depth, int a, int b, bool maxPlayer)
	{
		if (depth == 0) {
			return Evaluator::evaluate(board);
		}

		m_generator.calculate_moves_for(board);

		if (maxPlayer) {
			for (auto it = m_generator.begin(); it != m_generator.end(); it++) {
				a = std::max(a, alphabeta(*it, depth - 1, a, b, false));
				if (a <= b) {
					break;
				}
			}
			return a;
		} else {
			for (auto it = m_generator.begin(); it != m_generator.end(); it++) {
				b = std::min(b, alphabeta(*it, depth - 1, a, b, false));
				if (b <= a) {
					break;
				}
			}
			return b;
		}
	}
}
