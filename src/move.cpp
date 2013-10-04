#include <iostream>
#include <sstream>

#include "move.h"

namespace cengine 
{
	void Move::calculate_coordinates() const
	{

	}

	std::string Move::as_string() const
	{
		std::stringstream ss;
		ss << from << too;
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& o, const Move& m)
	{
		o << m.from << m.too;

		return o;
	}
}
