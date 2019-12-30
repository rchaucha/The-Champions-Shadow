#include "FrappeMortelle.h"
#include <vector>
#include "Character.h"
#include "Exhausted.h"

FrappeMortelle::FrappeMortelle() : AAttackDefinition(40)
{}

void FrappeMortelle::apply(Character* user, Character* target)
{
	unsigned int lowest_damage = 9,
		highest_damage = 17,
		damage = 0;

	damage = _attack(user, target, lowest_damage, highest_damage);

  std::vector<TwoDEntity> attack_entity_vect, effect_entity_vect;

  attack_entity_vect.push_back(TwoDEntity());
	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(),  _mana_consumption, attack_entity_vect, -(int)damage, _attack_spe_type));

	if (_attack_spe_type != AttackSpecificity::Failed && _attack_spe_type != AttackSpecificity::Missed)
	{
		unsigned short nbr_of_rounds = 1;
		
		Exhausted* exhausted = new Exhausted(user, nbr_of_rounds);

		target->addEffect(exhausted);

    attack_entity_vect.push_back(TwoDEntity());
		_attack_specificity.push_back(new AttackSpecificity(user, user, getNameId(), _mana_consumption, effect_entity_vect, exhausted));
	}

	_updateMana(user);
}