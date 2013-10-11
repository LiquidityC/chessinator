#include <iostream>
#include <sstream>
#include <cstdio>

#include "move.h"

namespace cengine 
{
	Move::Move(std::string f, std::string t) : from(f), to(t)
	{
		coordinates_to_bits();
		check_if_castling();
	}

	Move::Move(uint64_t f, uint64_t t) : from_bit(f), to_bit(t)
	{
		bits_to_coordinates();
		check_if_castling();
	}

	void Move::check_if_castling()
	{
		castling_move = false;
		if (from == "e1" && to == "g1") {
			castling_move = true;
		} else if (from == "e1" && to == "c1") {
			castling_move = true;
		} else if (from == "e8" && to == "g8") {
			castling_move = true;
		} else if (from == "e8" && to == "c8") {
			castling_move = true;
		}
	}

	std::string Move::as_string() const
	{
		std::stringstream ss;
		ss << from << to;
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& o, const Move& m)
	{
		o << m.as_string();

		return o;
	}

	void Move::bits_to_coordinates()
	{
		from = get_coordinate_for_bit(from_bit);
		to = get_coordinate_for_bit(to_bit);
	}

	std::string Move::get_coordinate_for_bit(const uint64_t& bit) const
	{
		int position = 1;
		while (bit>>position != 0) {
			position++;
		}

		unsigned int x_coord = position % 8;
		unsigned int y_coord = (position - x_coord) / 8;

		x_coord--;
		y_coord++;

		std::stringstream ss;
		ss << static_cast<char>('a' + x_coord);
		ss << y_coord;

		return ss.str();
	}

	void Move::coordinates_to_bits()
	{
		from_bit = get_bit_for_coordinate(from);
		to_bit = get_bit_for_coordinate(to);
	}

	uint64_t Move::get_bit_for_coordinate(const std::string& coordinate) const
	{
		unsigned int x, y;
	
		char x_char = coordinate[0];
		char y_char = coordinate[1];

		x = (x_char - ('a' - '1')) - '0';
		y = y_char - '0';

		return static_cast<uint64_t>(1)<<( (8*(y-1) + x)-1 );
	}

	bool Move::is_castling_move() const
	{
		return castling_move;
	}

	uint64_t Move::get_from_bit() const
	{
		return from_bit;
	}

	uint64_t Move::get_to_bit() const
	{
		return to_bit;
	}

	const std::string& Move::get_from_coord() const
	{
		return from;
	}

	const std::string& Move::get_to_coord() const
	{
		return to;
	}
}
