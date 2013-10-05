#include "player.h"
#include "countdowntimer.h"

namespace cengine
{
	Player::Player()
	{
		timer = new CountdownTimer();
	}

	Player::Player(const Player& player)
	{
		timer = new CountdownTimer(*player.timer);
	}

	Player::~Player()
	{
		delete timer;
	}

	Player& Player::operator=(const Player& player)
	{
		delete timer;
		timer = new CountdownTimer(*player.timer);

		return *this;
	}

	CountdownTimer& Player::get_timer()
	{
		return *timer;
	}

	void Player::set_name(std::string name)
	{
		this->name = name;
	}

	const std::string& Player::get_name() const
	{
		return name;
	}
}
