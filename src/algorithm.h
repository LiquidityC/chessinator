#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "board.h"
#include "movegenerator.h"

namespace cengine
{
	class Move;

	class Algorithm
	{
		private:

			int alphabeta(const Board&, unsigned int, int, int, bool);

			int quiescenceSearch(const Board&, unsigned int, int, int, bool);

		public:

			Move* get_move(const Board&);
	};
}

#endif
