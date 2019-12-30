#include "QuatriemeDimension.h"
#include "Character.h"
#include "Immobilised.h"
#include "Unattainable.h"

QuatriemeDimension::QuatriemeDimension() : AAttackDefinition(60)
{}

void QuatriemeDimension::apply(Character* user, Character* target)
{
	unsigned short nbr_of_rounds = rand() % (2 - 1) + 1; //nbr de tours = 1 OU 2

	Immobilised *immobilised = new Immobilised(target, nbr_of_rounds);
	Unattainable *unattainable = new Unattainable(target, nbr_of_rounds);

	target->addEffect(immobilised);
	target->addEffect(unattainable);

  std::vector<TwoDEntity> immobilised_entity_vect, unattainable_entity_vect;

  immobilised_entity_vect.push_back(TwoDEntity());
  unattainable_entity_vect.push_back(TwoDEntity());

	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, immobilised_entity_vect, immobilised));
	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, unattainable_entity_vect, unattainable));

	_updateMana(user);
}