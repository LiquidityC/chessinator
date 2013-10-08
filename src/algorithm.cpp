#include "algorithm.h"
#include "board.h"
#include "evaluator.h"
#include "movegenerator.h"

namespace cengine
{
	int Algorithm::alphabeta(const Board& board, unsigned int depth, int a, int b, bool maxPlayer)
	{
		if (depth == 0) {
			return Evaluator::evaluate(board);
		}

		m_generator.calculate_moves_for(board);

		if (maxPlayer) {
			for (it = m_generator.begin(); it != m_generator.end(); it++) {
				a = std::max(a, alphabeta(*it, depth - 1, a, b, false));
				if (a <= b) {
					break;
				}
			}
			return a;
		} else {
			for (it = m_generator.begin(); it != m_generator.end(); it++) {
				b = std::min(b, alphabeta(*it, depth - 1, a, b, false));
				if (b <= a) {
					break;
				}
			}
			return b;
		}
	}
}
