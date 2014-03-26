#include <unistd.h>
#include <fstream>
#include <iostream>

#include "controlcalculatortest.h"
#include "../src/board.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ControlCalculatorTest );

void ControlCalculatorTest::test_pawn_control()
{
	CPPUNIT_ASSERT(test_board("res/pawntest.txt", cengine::Color::BLACK) == static_cast<uint64_t>(0x0000FF0000000000));
	CPPUNIT_ASSERT(test_board("res/pawntest.txt", cengine::Color::WHITE) == static_cast<uint64_t>(0x0000000200FF0000));
}

uint64_t ControlCalculatorTest::test_board(std::string filename, cengine::Color color)
{
	std::ifstream file;
	file.open(filename);

	cengine::Board board;
	file >> board;
	file.close();

	cengine::ControlCalculator calculator;

	uint64_t control;

	if (color == cengine::Color::WHITE) {
		control = calculator.calculate_white_controlzone_for(board);
	} else {
		control = calculator.calculate_black_controlzone_for(board);
	}

	return control;
}
