#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "board.h"
#include "movegenerator.h"

namespace cengine
{
	class Algorithm
	{
		private:
			MoveGenerator m_generator;
			MoveGenerator::iterator it;

		public:
			int alphabeta(const Board&, unsigned int, int, int, bool);
	};
}

#endif
