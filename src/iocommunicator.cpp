#include <iostream>
#include <fstream>

#include "iocommunicator.h"
#include "move.h"
#include "iocommand.h"

namespace cengine
{
	IoCommand IoCommunicator::read_command()
	{
		char buffer[256];
		std::string input;

		std::cin.getline(buffer, 256);

		input = buffer;

		log_to_file("Recieved:\t", input);

		return IoCommand(input);
	}

	void IoCommunicator::send_command(const IoCommand& c) const
	{
		if (c.is_empty()) {
			return;
		}

		log_to_file("Sent: ", c.as_string());
		std::cout << c << std::endl;
	}

	void IoCommunicator::log_to_file(
			const std::string& tag, 
			const std::string& data) const
	{
		std::ofstream file;
		file.open("io.log", std::fstream::out | std::fstream::app);
		file << tag << data << std::endl;
		file.close();
	}
}
