#ifndef DEF_FRAPPEMORTELLE
#define DEF_FRAPPEMORTELLE

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class FrappeMortelle : public AAttackDefinition
{
public:
	FrappeMortelle();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "mortal_hit_description"; }
	std::string getNameId() override { return "mortal_hit_name"; }

	bool is_user_targeted_only() const { return false; }

protected:

private:

};

#endif