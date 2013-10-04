#ifndef MOVE_H
#define MOVE_H

#include <string>

namespace cengine
{
	class Move
	{
		private: // Variables
			int from_bin, too_bin;
			std::string from, too;

		private: // Functions

			void calculate_coordinates() const;

		public: // Functions

			Move(std::string f, std::string t) : from(f), too(t) { };

			~Move() { };

			std::string as_string() const;

			friend std::ostream& operator<<(std::ostream&, const cengine::Move&);
	};
}

#endif // MOVE_H
