#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>

#include "commandhandler.h"
#include "iocommand.h"

namespace cengine {

	IoCommand CommandHandler::parse_command(const IoCommand& command)
	{
		std::vector<std::string> tokens = command.get_tokens();

		std::string cmd = tokens[0];

		if (cmd == "xboard") {
			return IoCommand(get_feature_command_string());
		} else if (cmd == "new")  {
			// setup a new board
		} else if (cmd == "random")  {
			// play in random mode
		} else if (cmd == "level")  {
			// Command: level 40 5 0
			// It's tricky. Read about it here:
			// http://www.gnu.org/software/xboard/engine-intf.html#11
		} else if (cmd == "post")  {
			// Thinking output on: 
			// http://www.gnu.org/software/xboard/engine-intf.html#10
		} else if (cmd == "nopost")  {
			// Thinking off
		} else if (cmd == "hard")  {
			// Pondering on
			// Meaning: Thinking during op turn
			// Also known as: Permanent brain
		} else if (cmd == "easy")  {
			// Pondering off
		} else if (cmd == "time")  {
			time_cmd(tokens[1]);
		} else if (cmd == "otim")  {
			otim_cmd(tokens[1]);
		} else if (cmd == "ping")  {
			return IoCommand("pong " + tokens[1]);
		} else if (cmd == "protover")  {
			protover_cmd(tokens[1]);
		} else if (cmd == "name")  {
			// Opponent name
		} else if (cmd == "accepted")  {
			// Opponent name
		} else if (cmd == "rejected")  {
			// Opponent name
		} else {
			return IoCommand("Error (unknown command): " + cmd);
		}

		return IoCommand("");
	}

	std::string CommandHandler::get_feature_command_string()
	{
		std::string cmd;
		std::stringstream ss;

		ss << "feature "
			<< "ping=1 "
			<< "setboard=1 "
			<< "playother=1 "
			<< "myname=\"Batman\" "
			<< "variants=\"normal\" "
			<< "colors=0 "
			<< "name=1";

		cmd =  ss.str();

		return cmd;
	}

	void CommandHandler::protover_cmd(const std::string& cmd) 
	{
		if (cmd != "2") {
			std::cout << "Error (command not legal now): " << cmd << std::endl;
		}
	}

	void CommandHandler::time_cmd(const std::string& cmd)
	{
		//unsigned int engine_time = atoi(cmd.c_str());
	}

	void CommandHandler::otim_cmd(const std::string& cmd)
	{
		//unsigned int opponent_time = atoi(cmd.c_str());
	}
}
