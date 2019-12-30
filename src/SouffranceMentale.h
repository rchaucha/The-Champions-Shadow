#ifndef DEF_SOUFFRANCEMENTALE
#define DEF_SOUFFRANCEMENTALE

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class SouffranceMentale : public AAttackDefinition
{
public:
	SouffranceMentale();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "mental_hurt_description"; }
	std::string getNameId() override { return "mental_hurt_name"; }

	bool is_user_targeted_only() const { return false; }

protected:

private:

};

#endif
