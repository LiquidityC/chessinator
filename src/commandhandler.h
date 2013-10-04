#ifndef _COMMAND_HANDLER_H
#define _COMMAND_HANDLER_H

#include <string>

namespace cengine
{
	class IoCommand; // Forward declaration

	class CommandHandler
	{
		private: // Functions

			void protover_cmd(const std::string&);

			void time_cmd(const std::string&);

			void otim_cmd(const std::string&);

			std::string get_feature_command_string();

		public: // Functions

			IoCommand parse_command(const IoCommand&);

	};
}

#endif
