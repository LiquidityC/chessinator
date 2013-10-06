#include <iostream>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "iocommand.h"
#include "move.h"

namespace cengine
{
	bool IoCommand::is_move()
	{
		if (command.size() > 5 || command.size() < 4) {
			return false;
		}

		size_t i = 0;
		char c;
		while (i < 4) {
			c = command[i++];
			if ( c < 'a' || c > 'h') {
				return false;
			}
			c = command[i++];
			if ( c < '1' || c > '8') {
				return false;
			}
		}

		return true;
	}

	Move IoCommand::get_move()
	{
		assert (is_move()); // Sanity check

		std::string coord1, coord2;

		std::stringstream ss;
		ss << command[0] << command[1];
		coord1 = ss.str();
		ss.str("");

		ss << command[2] << command[3];
		coord2 = ss.str();
		ss.flush();

		return Move(coord1, coord2);
	}

	std::string IoCommand::as_string() const
	{
		return command;
	}

	std::ostream& operator<<(std::ostream& o, const IoCommand& c)
	{
		o << c.command;

		return o;
	}

	void IoCommand::parse_command()
	{
		std::istringstream iss(command);

		while (!iss.eof()) {
			std::string token;
			iss >> token;
			tokens.push_back(token);
		}
	}

	bool IoCommand::is_empty() const
	{
		return command.size() == 0;
	}

	const std::vector<std::string>& IoCommand::get_tokens() const
	{
		return tokens;
	}
}
