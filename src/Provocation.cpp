#include "Provocation.h"
#include "Character.h"
#include "Strenght.h"
#include "UnPrecision.h"

Provocation::Provocation() : AAttackDefinition(30)
{}

void Provocation::apply(Character* user, Character* target)
{
	bool is_applicable_at_every_turn = false,
		is_temporary = false;

	unsigned short nbr_of_rounds = 1;

	Strenght* strenght = new Strenght(target, nbr_of_rounds, is_applicable_at_every_turn, is_temporary, 1);
	UnPrecision* un_precision = new UnPrecision(target, nbr_of_rounds, is_applicable_at_every_turn, is_temporary, 2);

	target->addEffect(strenght);
	target->addEffect(un_precision);

  std::vector<TwoDEntity> strenght_entity_vect, un_precision_entity_vect;

  strenght_entity_vect.push_back(TwoDEntity());
  un_precision_entity_vect.push_back(TwoDEntity());

	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, strenght_entity_vect, strenght));
	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, un_precision_entity_vect, un_precision));

	_updateMana(user);
}