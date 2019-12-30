#include "Immobilised.h"
#include "Character.h"

Immobilised::Immobilised(Character* target, unsigned short nbr_of_rounds):
	Effect(target, nbr_of_rounds, false)
{}

Immobilised::~Immobilised()
{
	_target->setIsAbleToAttack(true);
}

void Immobilised::apply()
{
	if (!_is_first_turn_passed)
	{
		_target->setIsAbleToAttack(false);
		_is_first_turn_passed = true;
	}
}

