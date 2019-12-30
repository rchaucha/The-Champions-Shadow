#include "PremiersSecours.h"
#include "Character.h"

PremiersSecours::PremiersSecours() : AAttackDefinition(30)
{}

void PremiersSecours::apply(Character* user, Character* target)
{
	unsigned int lowest_damage = 2,
		highest_damage = 5,
		hp = 0;

	hp = _heal(user, user, lowest_damage, highest_damage);

  std::vector<TwoDEntity> attack_entity_vect;

  attack_entity_vect.push_back(TwoDEntity());
	_attack_specificity.push_back(new AttackSpecificity(user, user, getNameId(), _mana_consumption, attack_entity_vect, hp, _attack_spe_type));

	_updateMana(user);
}