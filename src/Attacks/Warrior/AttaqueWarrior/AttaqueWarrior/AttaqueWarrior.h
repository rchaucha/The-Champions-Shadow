#ifndef DEF_ATTAQUEWARRIOR
#define DEF_ATTAQUEWARRIOR

#include "../../../AbstractDamageAttack.h"
#include "../../../AbstractEffectAttack.h"

class Character;

class AttaqueWarrior : public AbstractDamageAttack, public AbstractEffectAttack
{
public:
	AttaqueWarrior();
	void attack(Character *user, Character *target);

protected:

private:

};

#endif