#include "SouffranceMentale.h"
#include "Character.h"

SouffranceMentale::SouffranceMentale() : AAttackDefinition(30)
{}

void SouffranceMentale::apply(Character* user, Character* target)
{
	unsigned int lowest_damage = 5,
		highest_damage = 10,
		damage = 0;

	damage = _attack(user, target, lowest_damage, highest_damage);

  std::vector<TwoDEntity> attack_entity_vect;

  attack_entity_vect.push_back(TwoDEntity());

	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, attack_entity_vect, -(int)damage, _attack_spe_type));

	_updateMana(user);
}