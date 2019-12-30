#include "Unattainable.h"
#include "Character.h"

Unattainable::Unattainable(Character* target, unsigned short nbr_of_rounds):
	Effect(target, nbr_of_rounds, false)
{}

Unattainable::~Unattainable()
{
	_target->setIsAttackable(true);
}

void Unattainable::apply()
{
	if (!_is_first_turn_passed)
	{
		_target->setIsAttackable(false);
		_is_first_turn_passed = true;
	}
}

