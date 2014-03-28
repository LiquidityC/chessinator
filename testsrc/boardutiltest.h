#ifndef _BOARD_UTIL_TEST_H
#define _BOARD_UTIL_TEST_H

#include <string>
#include "genericfixture.h"

namespace cengine
{
	class Board;
}

class BoardUtilTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( BoardUtilTest );
		CPPUNIT_TEST_SUITE_END();

	public:

		// We test nothing here at the moment

	private:

		cengine::Board load_board(std::string);
};

#endif
