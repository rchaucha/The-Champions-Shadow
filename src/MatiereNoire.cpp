#include "MatiereNoire.h"
#include "Character.h"
#include "UnPrecision.h"
#include "UnEvade.h"

MatiereNoire::MatiereNoire() : AAttackDefinition(30)
{}

void MatiereNoire::apply(Character* user, Character* target)
{
	unsigned int lowest_damage = 1,
		highest_damage = 3,
		damage = 0;

	damage = _attack(user, target, lowest_damage, highest_damage);
  
  std::vector<TwoDEntity> attack_entity_vect, un_evade_entity_vect, un_precision_entity_vect;

	_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, attack_entity_vect, -(int)damage, _attack_spe_type));

	if (_attack_spe_type != AttackSpecificity::Failed && _attack_spe_type != AttackSpecificity::Missed)
	{
		bool is_applicable_at_every_turn = false,
			is_temporary = true;

		unsigned short nbr_of_rounds = rand() % (3 - 2) + 2; //nbr de tours = 2 OU 3

		UnEvade* un_evade = new UnEvade(target, nbr_of_rounds, is_applicable_at_every_turn, is_temporary, 1);
		UnPrecision* un_precision = new UnPrecision(target, nbr_of_rounds, is_applicable_at_every_turn, is_temporary, 1);

		target->addEffect(un_evade);
		target->addEffect(un_precision);

    un_evade_entity_vect.push_back(TwoDEntity());
    un_precision_entity_vect.push_back(TwoDEntity());

		_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, un_evade_entity_vect, un_evade));
		_attack_specificity.push_back(new AttackSpecificity(user, target, getNameId(), _mana_consumption, un_precision_entity_vect, un_precision));
	}

	_updateMana(user);
}