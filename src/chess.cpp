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
			} else if (c.as_string() == "new") {
				Board new_board;
				board = new_board;
			}

			if (c.is_move()) {
				Move m = c.get_move();
				board.perform_move(m);

				Move* my_move = algorithm.get_move(board);
				if (my_move == NULL) {
					// We should be done, Game Over!
					continue;
				}

				board.perform_move(*my_move);
				io.send_command(IoCommand("move " + my_move->as_string()));

				delete my_move;

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
