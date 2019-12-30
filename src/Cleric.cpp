#include "Cleric.h"
#include "SouffranceMentale.h"
#include "MatiereNoire.h"
#include "QuatriemeDimension.h"
#include "PremiersSecours.h"

using namespace std;

Cleric::Cleric(string name) :Character(name, 1, 4, 3, 2)
{
	_attacks_list.push_back(shared_ptr<AAttackDefinition>(new SouffranceMentale()));
	_attacks_list.push_back(shared_ptr<AAttackDefinition>(new MatiereNoire()));
	_attacks_list.push_back(shared_ptr<AAttackDefinition>(new QuatriemeDimension()));
	_attacks_list.push_back(shared_ptr<AAttackDefinition>(new PremiersSecours()));
}

shared_ptr<AAttackDefinition> Cleric::aiAction(Character const &enemy) const
{
	vector<unsigned int> usable_attacks_id = _getUsableAttacks(enemy);

	int attack_id = rand() % usable_attacks_id.size();

	return _attacks_list[usable_attacks_id[attack_id]];
}