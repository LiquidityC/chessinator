#ifndef _IO_COMMAND_H
#define _IO_COMMAND_H

#include <string>
#include <vector>

namespace cengine 
{
	class Move; // Forward declaration

	class IoCommand
	{
		public: // Functions

			IoCommand() : command("") { parse_command(); };

			IoCommand(std::string s) : command(s) { parse_command(); };

			~IoCommand() { };

			bool is_move();

			Move get_move();

			bool is_empty() const;

			const std::vector<std::string>& get_tokens() const;

			std::string as_string() const;

			friend std::ostream& operator<<(std::ostream&, const IoCommand& c);

		private: // Variables

			std::string command;

			std::vector<std::string> tokens;

		private: // Functions

			void parse_command();

	};
}


#endif
