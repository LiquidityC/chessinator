#ifndef _IO_COMMUNICATOR_H
#define _IO_COMMUNICATOR_H

namespace cengine 
{
	class Move; // Forward declaration

	class IoCommunicator
	{
		public: // Functions

			IoCommunicator() { };

			~IoCommunicator() { };

			Move read_move();

			void send_move(const Move&) const;

		private: // Functions

			void log_to_file(const std::string&, const std::string&) const;
	};
}

#endif
