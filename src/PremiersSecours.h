#ifndef DEF_PREMIERSSECOURS
#define DEF_PREMIERSSECOURS

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class PremiersSecours : public AAttackDefinition
{
public:
	PremiersSecours();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "first_aid_description"; }
	std::string getNameId() override { return "first_aid_name"; }

	bool is_user_targeted_only() const { return true; }

protected:

private:

};

#endif