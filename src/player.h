#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>

namespace cengine
{
	class CountdownTimer; // Forward declare

	class Player
	{
		private:

			CountdownTimer* timer;

			std::string name;

		public:

			Player();

			Player(const Player&);

			~Player();

			CountdownTimer& get_timer();

			void set_name(std::string);

			const std::string& get_name() const;

			Player& operator=(const Player&);
	};
}

#endif
