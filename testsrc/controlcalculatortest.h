#ifndef _CONTROL_CALCULATOR_TEST_H
#define _CONTROL_CALCULATOR_TEST_H

#include "genericfixture.h"
#include "../src/controlcalculator.h"

class ControlCalculatorTest : public GenericFixture
{
	public:
		CPPUNIT_TEST_SUITE( ControlCalculatorTest );
		CPPUNIT_TEST( test_pawn_control );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_pawn_control();

	private:

		uint64_t test_board(std::string, cengine::Color);
};

#endif
