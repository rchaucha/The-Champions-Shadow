#ifndef DEF_ATTACKSPECIFITY
#define DEF_ATTACKSPECIFITY

#include <memory>
#include <string>
#include <vector>
#include "SFML\graphics.hpp"
#include "2DEntity.h"

class Character;
class Effect;

class AttackSpecificity
{
public:
	enum SkillType { EffectAttack, DamageAttack };
	enum AttackSpeType { Normal, Missed, Failed, Weakened, CriticalHit, UndefinedAttackType };

  AttackSpecificity(Character *user, Character *target, std::string const attack_name_id, unsigned short mana_consumption, std::vector<TwoDEntity> two_d_entities_vect, int const relative_life_change = 0, AttackSpeType const attack_spe = UndefinedAttackType);
	AttackSpecificity(Character *user, Character *target, std::string const attack_name_id, unsigned short mana_consumption, std::vector<TwoDEntity> two_d_entities_vect, Effect* effect = nullptr);
	~AttackSpecificity();

	const std::string getAttackNameId() const { return _attack_name_id; }
	const SkillType getSkillType() const { return _skill_type; }
	const AttackSpeType getAttackSpeType() const { return _attack_spe; }
  std::vector<TwoDEntity>& getTwoDEntitiesVect() { return _two_d_entities_vect; }
	const int getRelativeLifeChange() const { return _relative_life_change; }
	Character* getUser() const { return _user; }
	Character* getTarget() const { return _target; }
	Effect* getEffet() const { return _effect; }

private:
	int const _relative_life_change;
	std::string const _attack_name_id;

	AttackSpeType const _attack_spe;
  std::vector<TwoDEntity> _two_d_entities_vect;

	Effect* _effect;
	Character *_user,
		*_target;

	SkillType const _skill_type;

	unsigned short const _mana_consumption;
};

#endif