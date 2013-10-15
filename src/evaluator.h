#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "board.h"

namespace cengine
{
	class Evaluator
	{
		public:
			static int evaluate(const Board&);

		private:
			static int count_pieces(const Board& b, Unit);
	};
}

#endif
