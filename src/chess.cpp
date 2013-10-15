#include <iostream>

#include "chess.h"
#include "move.h"
#include "iocommunicator.h"
#include "iocommand.h"
#include "commandhandler.h"
#include "board.h"
#include "algorithm.h"

namespace cengine {

	int Chess::run()
	{
		IoCommunicator io;
		CommandHandler handler;
		Board board;
		Algorithm algorithm;

		while (true) {
			IoCommand c = io.read_command();

			if (c.as_string() == "quit") {
				break;
			}

			if (c.is_move()) {
				Move m = c.get_move();
				board.perform_move(m);

				Move my_move = algorithm.get_move(board);
				board.perform_move(my_move);
				io.send_command(IoCommand(my_move.as_string()));
			} else {
				io.send_command(handler.parse_command(c));
			}
		}

		return 0;
	}
}

int main(int argc, char** argv)
{
	cengine::Chess c;

	return c.run();
}
