#include <unistd.h>
#include <fstream>
#include <iostream>

#include "boardutiltest.h"
#include "../src/board.h"
#include "../src/boardutil.h"

CPPUNIT_TEST_SUITE_REGISTRATION( BoardUtilTest );

void BoardUtilTest::test_check()
{
	CPPUNIT_ASSERT( cengine::BoardUtil::is_white_in_check(load_board("res/testcheck.txt")) );
	CPPUNIT_ASSERT( cengine::BoardUtil::is_black_in_check(load_board("res/testcheck.txt")) );
}

cengine::Board BoardUtilTest::load_board(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	cengine::Board board;
	file >> board;
	file.close();

	return board;
}
