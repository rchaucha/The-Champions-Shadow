#ifndef DEF_QUATRIEMEDIMENSION
#define DEF_QUATRIEMEDIMENSION

#include "LangManager.h"
#include "AAttackDefinition.h"

class Character;

class QuatriemeDimension : public AAttackDefinition
{
public:
	QuatriemeDimension();
	void apply(Character* user, Character* target) override;
	std::string getDescriptionId() override { return "fourth_dimension_description"; }
	std::string getNameId() override { return "fourth_dimension_name"; }

	bool is_user_targeted_only() const { return false; }

protected:

private:

};

#endif