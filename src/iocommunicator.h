#ifndef _IO_COMMUNICATOR_H
#define _IO_COMMUNICATOR_H

namespace cengine 
{
	class IoCommand; // Forward declaration

	class IoCommunicator
	{
		public: // Functions

			IoCommunicator() { };

			~IoCommunicator() { };

			IoCommand read_command();

			void send_command(const IoCommand&) const;

		private: // Functions

			void log_to_file(const std::string&, const std::string&) const;
	};
}

#endif
