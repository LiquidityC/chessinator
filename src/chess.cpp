#include <iostream>

#include "chess.h"
#include "move.h"
#include "iocommunicator.h"
#include "iocommand.h"
#include "commandhandler.h"
#include "boardutil.h"
#include "board.h"

namespace cengine {

	int Chess::run()
	{
		IoCommunicator io;
		CommandHandler handler;
		Board b = BoardUtil::create_board();

		while (true) {
			IoCommand c = io.read_command();
			IoCommand response;

			if (c.as_string() == "quit") {
				break;
			}

			if (c.is_move()) {
				Move m = c.get_move();
				BoardUtil::perform_move(m, b);
			} else {
				response = handler.parse_command(c);
			}

			io.send_command(response);
		}

		return 0;
	}
}

int main(int argc, char** argv)
{
	cengine::Chess c;

	return c.run();
}
