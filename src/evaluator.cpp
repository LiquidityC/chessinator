#include "evaluator.h"

namespace cengine
{
	int Evaluator::evaluate(const Board& b)
	{
		int score = b.pieces[ALL_BLACK_PIECES] ^ b.pieces[ALL_WHITE_PIECES];
		return ~score;
	}
}
