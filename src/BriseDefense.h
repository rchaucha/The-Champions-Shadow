#ifndef DEF_BRISEDEFNESE
#define DEF_BRISEDEFNESE

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class BriseDefense : public AAttackDefinition
{
public:
	BriseDefense();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "defense_breaker_description"; }
	std::string getNameId() override { return "defense_breaker_name"; }

	bool is_user_targeted_only() const { return false; }

protected:

private:

};

#endif