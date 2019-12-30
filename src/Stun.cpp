#include "Stun.h"
#include "Character.h"

Stun::Stun(Character* target, unsigned short nbr_of_rounds):
	Effect(target, nbr_of_rounds, false)
{}

Stun::~Stun()
{
	_target->setIsAbleToAttack(true);
}

void Stun::apply()
{
	if (!_is_first_turn_passed)
	{
		_target->setIsAbleToAttack(false);
		_is_first_turn_passed = true;
	}
}

