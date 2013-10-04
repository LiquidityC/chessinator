#include <iostream>

#include "chess.h"
#include "move.h"
#include "iocommunicator.h"

namespace cengine {

	Chess::Chess() 
	{
		std::cout << "Chess engine starting" << std::endl;
	}

	int Chess::run()
	{
		bool running = true;

		IoCommunicator io;

		while (running) {
			Move m = io.read_move();
		}

		return 0;
	}
}

int main(int argc, char** argv)
{
	cengine::Chess c;

	return c.run();
}
