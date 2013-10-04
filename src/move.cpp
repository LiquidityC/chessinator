#include <iostream>

#include "move.h"

namespace cengine 
{
	void Move::calculate_coordinates() const
	{

	}

	void Move::print_move() const
	{
		std::cout << "Move: " << from << " -> " << too << std::endl;

	}

	std::ostream& operator<<(std::ostream& o, const cengine::Move& m)
	{
		o << m.from << m.too;

		return o;
	}
}
