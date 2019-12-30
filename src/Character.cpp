#include "Character.h"
#include "Effect.h"
#include "FrappeMortelle.h"
#include "BriseDefense.h"
#include "Provocation.h"

using namespace std;

Character::Character(string name, int strenght, int defense, int precision, int evade, unsigned int life, unsigned short mana) :
	_max_life(life),
	_life(life),
	_name(name),
	_strenght(strenght),
	_defense(defense),
	_precision(precision),
	_evade(evade),
	_unable_to_attack_counter(0),
	_unable_to_be_attacked_counter(0),
	_mana(mana),
	_max_mana(mana)
{}

unsigned int Character::takeDamage(unsigned int amout)
{
	if (amout > _life) //si les dégats sont supérieurs à la vie restante
	{
		amout = _life;
	}

	_life -= amout;

	return amout;
}

unsigned int Character::heal(unsigned int amout)
{
	if (amout + _life > _max_life) //si les points de soin + la vie sont supérieurs à la vie max
	{
		amout = _max_life - _life;
	}

	_life += amout;

	return amout;
}

bool Character::subtractMana(unsigned short amout)
{
	if (amout > _mana)
		return false;
	else
	{
		_mana -= amout;;
		return true;
	}
}

void Character::addMana(unsigned short amout)
{
	if (amout + _mana > _max_mana)
		amout = _max_mana - _mana;

	_mana += amout;
}

vector<string> Character::getAttacksNameList(LangManager const *lang_manager)
{
	vector<string > attacks_list_vector(_getNumberOfAttacks());

	for (unsigned int i = 0; i < _attacks_list.size(); i++)
	{
		string name = lang_manager->getStrById(_attacks_list[i]->getNameId(), 0);

		attacks_list_vector[i] = name;
	}

	return attacks_list_vector;
}

map<string, string> Character::getAttacksDescription(LangManager const *lang_manager)
{
	map<string, string > attacks_description_map;

	for (unsigned int i = 0; i < _attacks_list.size(); i++)
	{
		string name = lang_manager->getStrById(_attacks_list[i]->getNameId(), 0),
			description = lang_manager->getStrById(_attacks_list[i]->getDescriptionId());

		attacks_description_map[name] = description;
	}

	return attacks_description_map;
}

vector<unsigned int> Character::_getUsableAttacks(Character const &enemy) const
{
	vector<unsigned int> usable_attacks_id;

	if (!enemy.canBeAttacked())
	{
		unsigned int id = 0;
		for (shared_ptr<AAttackDefinition> attack : _attacks_list)
		{
			if (attack->is_user_targeted_only()) //si l'utilisateur est la seule cible, on peut utiliser l'attaque
				usable_attacks_id.push_back(id);
			id++;
		}
	}
	else
	{
		for (unsigned int id = 0; id < _attacks_list.size(); id++)
		{
			usable_attacks_id.push_back(id);
		}
	}

	return usable_attacks_id;
}

void Character::addEffect(Effect* effect)
{
	_effects.push_back(effect);
}

void Character::updateEffects()
{
	auto it = _effects.begin();

	while (it != _effects.end())
	{
		Effect* current_effect = *it;

		if (current_effect->isFinished()) //si l'effet a fini son nombre de tour prédéfini, on le supprime
		{
			delete current_effect;
			it = _effects.erase(it);
		}
		else
		{
			current_effect->apply();
			current_effect->oneRoundPassed();

			it++;
		}
	}
	_effects.shrink_to_fit();
}