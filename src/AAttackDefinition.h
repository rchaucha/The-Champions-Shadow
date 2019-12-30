#ifndef DEF_AATTACKDEFINITION
#define DEF_AATTACKDEFINITION

#include <vector>
#include <memory>
#include "LangManager.h"
#include "IAttackDefinition.h"
#include "AttackSpecificity.h"
#include "Effect.h"

class Character;

class AAttackDefinition : public IAttackDefinition
{
public:
	AAttackDefinition(unsigned short mana_consumption): 
		_mana_consumption(mana_consumption)
	{}

	virtual ~AAttackDefinition() {}

	std::vector<AttackSpecificity*> getAttackSpecificity() { return _attack_specificity; }
	unsigned short getManaConsumption() { return _mana_consumption; }

	void reset();

	virtual bool is_user_targeted_only() const = 0;
protected:
	unsigned int _attack(const Character *user, Character *target, unsigned int lowest_damage, unsigned int highest_damage, int precision = 0);
	unsigned int _heal(const Character *user, Character *target, unsigned int lowest_hp, unsigned int highest_hp, int precision = 0);

	void _updateMana(Character *user);

	AttackSpecificity::AttackSpeType _attack_spe_type;

	std::vector<AttackSpecificity*> _attack_specificity;

	unsigned short _mana_consumption;

private:
	unsigned int _dealDamage(const Character *user, Character *target, int lowest_damage, int highest_damage) const;
	unsigned int _concreteHeal(Character *target, int lowest_hp, int highest_hp) const;
};

#endif