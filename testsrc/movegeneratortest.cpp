#include <unistd.h>
#include <fstream>
#include <iostream>

#include "movegeneratortest.h"
#include "../src/movegenerator.h"
#include "../src/board.h"
#include "../src/boardutil.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MoveGeneratorTest );

void MoveGeneratorTest::test_move()
{
	CPPUNIT_ASSERT(test_board("res/startboard.txt") == 20);
	CPPUNIT_ASSERT(test_board("res/testking.txt") == 8);
	CPPUNIT_ASSERT(test_board("res/testcastling.txt") == 24);
	CPPUNIT_ASSERT(test_board("res/testqueen.txt") == 30);
}

int MoveGeneratorTest::test_board(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	cengine::MoveGenerator generator;
	cengine::Board board = cengine::BoardUtil::create_board(file);
	file.close();

	generator.calculate_moves_for(board);
	return generator.move_count();
}
