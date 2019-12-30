#ifndef DEF_UNDEFENSE
#define DEF_UNDEFENSE

#include "Effect.h"

class UnDefense : public Effect
{
public:
	UnDefense(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~UnDefense();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("undefense_render"); }
private:
};
#endif