#include "evaluator.h"

namespace cengine
{
	int Evaluator::evaluate(const Board& b)
	{
		int score = b.get_pieces_for(ALL_BLACK_PIECES) ^ b.get_pieces_for(ALL_WHITE_PIECES);
		return ~score;
	}
}
