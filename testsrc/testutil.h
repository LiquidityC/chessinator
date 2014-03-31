#ifndef _TEST_UTIL_H
#define _TEST_UTIL_H

#include <string>

namespace cengine
{
	class Board;
}

class TestUtil
{
	public:
		static cengine::Board load_board(std::string);
};

#endif
