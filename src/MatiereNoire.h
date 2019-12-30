#ifndef DEF_MATIERENOIRE
#define DEF_MATIERENOIRE

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class MatiereNoire : public AAttackDefinition
{
public:
	MatiereNoire();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "dark_matter_description"; }
	std::string getNameId() override { return "dark_matter_name"; }

	bool is_user_targeted_only() const { return false; }

protected:

private:

};

#endif