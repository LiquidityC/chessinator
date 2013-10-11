#ifndef _BOARD_UTIL_TEST_H
#define _BOARD_UTIL_TEST_H

#include "genericfixture.h"

class BoardUtilTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( BoardUtilTest );
		CPPUNIT_TEST( test_move );
		CPPUNIT_TEST( test_castling_move );
		CPPUNIT_TEST( test_take );
		CPPUNIT_TEST( test_totals );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_move();
		void test_castling_move();
		void test_take();
		void test_totals();
};

#endif
