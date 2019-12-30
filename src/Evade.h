#ifndef DEF_EVADE
#define DEF_EVADE

#include "Effect.h"

class Evade : public Effect
{
public:
	Evade(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~Evade();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("evade_render"); }
private:
};
#endif