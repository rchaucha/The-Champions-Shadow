#include "AAttackDefinition.h"

#include <math.h>
#include "Character.h"

void AAttackDefinition::reset()
{
	_attack_spe_type = AttackSpecificity::AttackSpeType::UndefinedAttackType;
	_attack_specificity.clear();
}

unsigned int AAttackDefinition::_attack(const Character *user, Character *target, unsigned int lowest_damage, unsigned int highest_damage, int precision)
{
	unsigned int damage = 0;
	_attack_spe_type = AttackSpecificity::AttackSpeType::UndefinedAttackType;

	int miss_stats = precision + user->getPrecision() - target->getEvade();

	if (miss_stats < -7) //minimum : 1/2 chance de rater
	{
		miss_stats = -7;
	}
	else if (miss_stats > 11) //max : 1/10 de rater
	{
		miss_stats = 11;
	}

	int miss = rand() % (9 + miss_stats);
	if (miss != 0) //si l'attaque ne rate pas
	{
		int weakness = rand() % 7;
		if (weakness != 0) //si l'attaque n'est pas affaiblie
		{
			int critical = rand() % 5;
			if (critical == 0) //si c'est un coup critique
			{
				_attack_spe_type = AttackSpecificity::AttackSpeType::CriticalHit;

				damage = _dealDamage(user, target, lowest_damage + 1, highest_damage + 2);
			}
			else //attaque normale
			{
				_attack_spe_type = AttackSpecificity::AttackSpeType::Normal;

				damage = _dealDamage(user, target, lowest_damage, highest_damage);
			}
		}
		else //attaque affaiblie
		{
			_attack_spe_type = AttackSpecificity::AttackSpeType::Weakened;

			damage = _dealDamage(user, target, lowest_damage - 2, highest_damage - 1);
		}
	}
	else //si l'attaque rate
	{
		_attack_spe_type = AttackSpecificity::AttackSpeType::Missed;

		damage = 0;
	}

	return damage;
}

unsigned int AAttackDefinition::_heal(const Character * user, Character * target, unsigned int lowest_hp, unsigned int highest_hp, int precision)
{
	unsigned int hp = 0;
	_attack_spe_type = AttackSpecificity::AttackSpeType::UndefinedAttackType;

	int miss_stats = precision + user->getPrecision();

	if (miss_stats < -7) //minimum : 1/2 chance de rater
	{
		miss_stats = -7;
	}
	else if (miss_stats > 11) //max : 1/10 de rater
	{
		miss_stats = 11;
	}

	int miss = rand() % (9 + miss_stats);
	if (miss != 0) //si l'attaque ne rate pas
	{
		_attack_spe_type = AttackSpecificity::AttackSpeType::Normal;

		hp = _concreteHeal(target, lowest_hp, highest_hp);
	}
	else
	{
		_attack_spe_type = AttackSpecificity::AttackSpeType::Failed;

		hp = 0;
	}

	return hp;
}

void AAttackDefinition::_updateMana(Character * user)
{
	user->subtractMana(_mana_consumption);
}

unsigned int AAttackDefinition::_dealDamage(const Character *user, Character *target, int lowest_damage, int highest_damage) const
{
	if (lowest_damage < 0)
		lowest_damage = 0;

	if (highest_damage < 0)
		highest_damage = 0;

	unsigned int damage = rand() % (highest_damage - lowest_damage) + lowest_damage; //créer les degats entre les deux bornes de l'attaque

	damage += user->getStrenght();

	{
		int damage_test = damage - target->getDefense();

		if (damage_test > 0) //si on peut enlever la defense au dégats sans passer en négatif
			damage -= target->getDefense();
		else
			damage = 0;
	}
	
	{
		unsigned int temp_damage = damage * (rand() % (135 - 65) + 65);
		damage = (unsigned int)round(temp_damage / 100); //coeficient variant entre 0.65 ~ 1.35
	}

	damage = target->takeDamage(damage);

	return damage;
}

unsigned int AAttackDefinition::_concreteHeal(Character * target, int lowest_hp, int highest_hp) const
{
	if (lowest_hp < 0)
		lowest_hp = 0;

	if (highest_hp < 0)
		highest_hp = 0;

	unsigned int hp = rand() % (highest_hp - lowest_hp) + lowest_hp; //créer les pv entre les deux bornes du soin

	hp = target->heal(hp);

	return hp;
}
