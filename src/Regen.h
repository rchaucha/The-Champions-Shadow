#ifndef DEF_REGEN
#define DEF_REGEN

#include "Effect.h"

class Regen : public Effect
{
public:
	Regen(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~Regen();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("regen_render"); }
private:
};
#endif