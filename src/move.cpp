#include <iostream>
#include <sstream>

#include "move.h"

namespace cengine 
{
	Move::Move(std::string f, std::string t) : from(f), to(t)
	{
		calculate_coordinates();
	}

	std::string Move::as_string() const
	{
		std::stringstream ss;
		ss << from << to;
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& o, const Move& m)
	{
		o << m.from << m.to;

		return o;
	}

	void Move::calculate_coordinates()
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
