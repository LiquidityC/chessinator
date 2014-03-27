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
		CPPUNIT_TEST( test_check );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_check();

	private:

		cengine::Board load_board(std::string);
};

#endif
