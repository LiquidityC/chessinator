#ifndef MOVE_H
#define MOVE_H

#include <string>

namespace cengine
{
	class Move
	{
		private: // Variables
			uint64_t from_bit, to_bit;
			std::string from, to;
			bool castling_move;

		private: // Functions

			void bits_to_coordinates();

			std::string get_coordinate_for_bit(const uint64_t& bit) const;

			void coordinates_to_bits();

			uint64_t get_bit_for_coordinate(const std::string& coordinate) const;

			void check_if_castling();

		public: // Functions

			Move(std::string f, std::string t);

			Move(uint64_t, uint64_t);

			~Move() { };

			std::string as_string() const;

			const std::string& get_from_coord() const;

			const std::string& get_to_coord() const;

			uint64_t get_from_bit() const;

			uint64_t get_to_bit() const;

			bool is_castling_move() const;

			friend std::ostream& operator<<(std::ostream&, const cengine::Move&);
	};
}

#endif // MOVE_H
