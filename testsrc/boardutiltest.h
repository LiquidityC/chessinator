#ifndef _BOARD_UTIL_TEST_H
#define _BOARD_UTIL_TEST_H

#include "genericfixture.h"

class BoardUtilTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( BoardUtilTest );
		CPPUNIT_TEST( test_move );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_move();
};

#endif
