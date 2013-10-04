#include <iostream>

#include "chess.h"
#include "move.h"
#include "iocommunicator.h"
#include "iocommand.h"
#include "commandhandler.h"

namespace cengine {

	int Chess::run()
	{
		bool running = true;

		IoCommunicator io;
		CommandHandler handler;

		while (running) {
			IoCommand c = io.read_command();
			IoCommand response;

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
