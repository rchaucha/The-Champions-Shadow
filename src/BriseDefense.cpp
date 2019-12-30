#include "BriseDefense.h"
#include "Character.h"
#include "UnDefense.h"

BriseDefense::BriseDefense() : AAttackDefinition(40)
{}

void BriseDefense::apply(Character* user, Character* target)
{
	unsigned int lowest_damage = 2,
		highest_damage = 5,
		damage = 0;

	damage = _attack(user, target, lowest_damage, highest_damage);

  std::vector<TwoDEntity> attack_entity_vect, effect_entity_vect;

  attack_entity_vect.push_back(TwoDEntity());

	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, attack_entity_vect, -(int)damage, _attack_spe_type));

	if (_attack_spe_type != AttackSpecificity::Failed && _attack_spe_type != AttackSpecificity::Missed)
	{
		bool is_applicable_at_every_turn = false,
			is_temporary = false;

		unsigned short nbr_of_rounds = 1;

		UnDefense* un_defense = new UnDefense(target, nbr_of_rounds, is_applicable_at_every_turn, is_temporary, 1);

		target->addEffect(un_defense);

    effect_entity_vect.push_back(TwoDEntity());

		_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, effect_entity_vect, un_defense));
	}

	_updateMana(user);
}