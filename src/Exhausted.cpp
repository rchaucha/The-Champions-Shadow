#include "Exhausted.h"
#include "Character.h"

Exhausted::Exhausted(Character* target, unsigned short nbr_of_rounds):
	Effect(target, nbr_of_rounds, false)
{}

Exhausted::~Exhausted()
{
	_target->setIsAbleToAttack(true);
}

void Exhausted::apply()
{
	if (!_is_first_turn_passed)
	{
		_target->setIsAbleToAttack(false);
		_is_first_turn_passed = true;
	}
}

