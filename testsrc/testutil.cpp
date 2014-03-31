#include <unistd.h>
#include <fstream>
#include <iostream>

#include "testutil.h"
#include "../src/board.h"

cengine::Board TestUtil::load_board(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	cengine::Board board;
	file >> board;
	file.close();

	return board;
}
