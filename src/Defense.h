#ifndef DEF_DEFENSE
#define DEF_DEFENSE

#include "Effect.h"

class Defense : public Effect
{
public:
	Defense(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~Defense();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("defense_render"); }
private:
};
#endif