#include "Warrior.h"
#include "FrappeMortelle.h"
#include "BriseDefense.h"
#include "Provocation.h"

using namespace std;

Warrior::Warrior(string name) :Character(name, 4, 3, 1, 2)
{
   _attacks_list.push_back(shared_ptr<AAttackDefinition>(new FrappeMortelle()));
   _attacks_list.push_back(shared_ptr<AAttackDefinition>(new BriseDefense()));
   _attacks_list.push_back(shared_ptr<AAttackDefinition>(new Provocation()));
}

shared_ptr<AAttackDefinition> Warrior::aiAction(Character const &enemy) const
{
	vector<unsigned int> usable_attacks_id = _getUsableAttacks(enemy);

	int attack_id = rand() % usable_attacks_id.size();

	return _attacks_list[usable_attacks_id[attack_id]];
}