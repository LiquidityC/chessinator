#include <unistd.h>
#include <fstream>
#include <iostream>

#include "controlcalculatortest.h"
#include "../src/board.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ControlCalculatorTest );

void ControlCalculatorTest::test_pawn_control()
{
	CPPUNIT_ASSERT(test_board("res/pawntest.txt", cengine::Color::BLACK) == static_cast<uint64_t>(0x7EFFFF0000000000));
	CPPUNIT_ASSERT(test_board("res/pawntest.txt", cengine::Color::WHITE) == static_cast<uint64_t>(0x0000000201FFFF7E));
}

void ControlCalculatorTest::test_queen_control()
{
	CPPUNIT_ASSERT(test_board("res/testqueen.txt", cengine::Color::WHITE) == static_cast<uint64_t>(0x88492A1CF71F2A4B));
}

void ControlCalculatorTest::test_rook_control()
{
	CPPUNIT_ASSERT(test_board("res/testrooks.txt", cengine::Color::WHITE) == static_cast<uint64_t>(0x80808F708080B0A));
}

void ControlCalculatorTest::test_king_control()
{
	CPPUNIT_ASSERT(test_board("res/testking.txt", cengine::Color::WHITE) == static_cast<uint64_t>(0x00001C141C000000));
	CPPUNIT_ASSERT(test_board("res/testking.txt", cengine::Color::BLACK) == static_cast<uint64_t>(0x0000000070507000));
}

void ControlCalculatorTest::test_bishop_control()
{
	CPPUNIT_ASSERT(test_board("res/testcastlingblock.txt", cengine::Color::BLACK) == static_cast<uint64_t>(0x2838804020110A00));
}

void ControlCalculatorTest::test_knight_control()
{

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
