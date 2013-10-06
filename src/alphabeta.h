#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "board.h"

namespace cengine
{
	class AlphaBeta
	{
		public:
			long run(Board, unsigned int, long, long, bool);
	};
}

#endif
