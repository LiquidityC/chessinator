#ifndef _BOARD_TEST_H
#define _BOARD_TEST_H

#include "genericfixture.h"
#include "../src/board.h"

class BoardTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( BoardTest );
		CPPUNIT_TEST( test_move );
		CPPUNIT_TEST( test_castling_move );
		CPPUNIT_TEST( test_take );
		CPPUNIT_TEST( test_totals );
		CPPUNIT_TEST( test_pawn_promotion );
		CPPUNIT_TEST_SUITE_END();

	private:

		cengine::Board load_board(std::string);

	public:

		void test_move();
		void test_castling_move();
		void test_take();
		void test_totals();
		void test_pawn_promotion();
};

#endif
