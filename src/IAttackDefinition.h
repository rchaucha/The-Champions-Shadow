#ifndef DEF_IATTACKDEFINITION
#define DEF_IATTACKDEFINITION

#include <string>
#include <vector>
#include "SFML\graphics.hpp"
#include "AttackSpecificity.h"

class Character;

class IAttackDefinition
{
public:
	virtual ~IAttackDefinition() {}

	virtual void apply(Character* user, Character* target) = 0;

	virtual std::string getDescriptionId() = 0;
	virtual std::string getNameId() = 0;

protected:

private:

};

#endif