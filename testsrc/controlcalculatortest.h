#ifndef _CONTROL_CALCULATOR_TEST_H
#define _CONTROL_CALCULATOR_TEST_H

#include "genericfixture.h"
#include "../src/controlcalculator.h"

class ControlCalculatorTest : public GenericFixture
{
	public:
		CPPUNIT_TEST_SUITE( ControlCalculatorTest );
		CPPUNIT_TEST( test_pawn_control );
		CPPUNIT_TEST( test_rook_control );
		CPPUNIT_TEST( test_knight_control );
		CPPUNIT_TEST( test_bishop_control );
		CPPUNIT_TEST( test_queen_control );
		CPPUNIT_TEST( test_king_control );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_pawn_control();
		void test_rook_control();
		void test_knight_control();
		void test_bishop_control();
		void test_queen_control();
		void test_king_control();

	private:

		uint64_t test_board(std::string, cengine::Color);
};

#endif
