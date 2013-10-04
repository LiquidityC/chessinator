#include <iostream>
#include <fstream>

#include "iocommunicator.h"
#include "move.h"

namespace cengine
{
	Move IoCommunicator::read_move()
	{
		std::string input;

		std::cin >> input;

		log_to_file("Recieved:\t", input);

		return Move("e1", "e2");
	}

	void IoCommunicator::send_move(const Move& m) const
	{
		std::cout << m << std::endl;
	}

	void IoCommunicator::log_to_file(const std::string& tag, const std::string& data) const
	{
		std::ofstream file;
		file.open("io.log", std::fstream::out | std::fstream::app);
		file << tag << data << std::endl;
		file.close();
	}
}
