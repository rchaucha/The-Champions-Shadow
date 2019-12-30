#ifndef DEF_PROVOCATION
#define DEF_PROVOCATION

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class Provocation : public AAttackDefinition
{
public:
	Provocation();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "provocation_description"; }
	std::string getNameId() override { return "provocation_name"; }

	bool is_user_targeted_only() const { return false; }

protected:

private:

};

#endif