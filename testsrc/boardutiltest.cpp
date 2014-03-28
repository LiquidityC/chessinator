#include <unistd.h>
#include <fstream>
#include <iostream>

#include "boardutiltest.h"
#include "../src/board.h"
#include "../src/boardutil.h"

CPPUNIT_TEST_SUITE_REGISTRATION( BoardUtilTest );

cengine::Board BoardUtilTest::load_board(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	cengine::Board board;
	file >> board;
	file.close();

	return board;
}
