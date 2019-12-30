#include "AttackSpecificity.h"
#include "Character.h"
#include "Effect.h"

using namespace std;

AttackSpecificity::AttackSpecificity(Character * user, Character * target, string const attack_name_id, unsigned short mana_consumption, vector<TwoDEntity> two_d_entities_vect, int const relative_life_change, AttackSpeType attack_spe) :
_user(user),
_target(target),
_attack_name_id(attack_name_id),
_mana_consumption(mana_consumption),
_two_d_entities_vect(two_d_entities_vect),
_relative_life_change(relative_life_change),
_attack_spe(attack_spe),
_effect(nullptr),
_skill_type(SkillType::DamageAttack)
{}

AttackSpecificity::AttackSpecificity(Character * user, Character * target, string const attack_name_id, unsigned short mana_consumption, vector<TwoDEntity> two_d_entities_vect, Effect* effect) :
_user(user),
_target(target),
_attack_name_id(attack_name_id),
_mana_consumption(mana_consumption),
_two_d_entities_vect(two_d_entities_vect),
_relative_life_change(0),
_attack_spe(AttackSpeType::UndefinedAttackType),
_effect(effect),
_skill_type(SkillType::EffectAttack)
{}

AttackSpecificity::~AttackSpecificity()
{
  delete _user;
  _user = nullptr;

  delete _target;
  _target = nullptr;

  delete _effect;
  _effect = nullptr;
}
