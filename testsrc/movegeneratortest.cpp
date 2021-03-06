#include <unistd.h>
#include <fstream>
#include <iostream>

#include "movegeneratortest.h"
#include "../src/movegenerator.h"
#include "../src/board.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MoveGeneratorTest );

void MoveGeneratorTest::test_move()
{
	CPPUNIT_ASSERT(test_board("res/testqueen.txt") == 32);
	CPPUNIT_ASSERT(test_board("res/testking.txt") == 8);
	CPPUNIT_ASSERT(test_board("res/startboard.txt") == 20);
	CPPUNIT_ASSERT(test_board("res/startboard.txt", false) == 20);
	CPPUNIT_ASSERT(test_board("res/testcastling.txt") == 26);
	CPPUNIT_ASSERT(test_board("res/testcastlingblock.txt") == 23);
	CPPUNIT_ASSERT(test_board("res/testcastlingcheckblock.txt") == 20);
	CPPUNIT_ASSERT(test_board("res/testblackpieces.txt", false) == 6);
	CPPUNIT_ASSERT(test_board("res/pawntest.txt", true) == 21);
	CPPUNIT_ASSERT(test_board("res/testcheckmate.txt") == 0);
}

int MoveGeneratorTest::test_board(std::string filename, bool whites_turn)
{
	std::ifstream file;
	file.open(filename);

	cengine::MoveGenerator generator;
	cengine::Board board;
	file >> board;
	file.close();

	board.set_whites_turn(whites_turn);
	generator.calculate_moves_for(board);

	return generator.move_count();
}
