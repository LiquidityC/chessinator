#include <iostream>

#include "chess.h"
#include "move.h"
#include "iocommunicator.h"
#include "iocommand.h"
#include "commandhandler.h"
#include "player.h"

namespace cengine {

	int Chess::run()
	{
		IoCommunicator io;
		CommandHandler handler;
		Player player1, player2;

		while (true) {
			IoCommand c = io.read_command();
			IoCommand response;

			if (c.as_string() == "quit") {
				break;
			}

			if (c.is_move()) {
				// Perform the move
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
