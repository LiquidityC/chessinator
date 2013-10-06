#ifndef MOVE_H
#define MOVE_H

#include <string>

namespace cengine
{
	class Move
	{
		private: // Variables
			int64_t from_bit, to_bit;
			std::string from, to;

		private: // Functions

			void calculate_coordinates();

			int64_t get_bit_for_coordinate(const std::string& coordinate) const;

		public: // Functions

			Move(std::string f, std::string t);

			~Move() { };

			std::string as_string() const;

			const std::string& get_from_coord() const;

			const std::string& get_to_coord() const;

			int64_t get_from_bit() const;

			int64_t get_to_bit() const;

			friend std::ostream& operator<<(std::ostream&, const cengine::Move&);
	};
}

#endif // MOVE_H
