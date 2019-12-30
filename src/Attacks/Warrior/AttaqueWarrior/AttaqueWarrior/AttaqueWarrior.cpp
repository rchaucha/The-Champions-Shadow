// AttaqueWarrior.cpp : Defines the exported functions for the DLL application.

#include "stdafx.h"
#include "AttaqueWarrior.h"
#include "../../../../Character.h"

AttaqueWarrior::AttaqueWarrior() : AbstractDamageAttack(), AbstractEffectAttack()
{}

void AttaqueWarrior::attack(Character *user, Character *target)
{
	unsigned int lowest_damage = 9,
		highest_damage = 17,
		damage = 0;
	damage = AbstractDamageAttack::_attack(user, target, lowest_damage, highest_damage);

	unsigned int nbr_of_rounds = 1;
	bool is_applicable_at_every_turn = false;
	AbstractEffectAttack::_addEffect(user, user, Effect::Stun, nbr_of_rounds, is_applicable_at_every_turn);
}