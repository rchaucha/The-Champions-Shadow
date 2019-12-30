#ifndef DEF_STRENGHT
#define DEF_STRENGHT

#include "Effect.h"

class Strenght : public Effect
{
public:
	Strenght(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~Strenght();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("strenght_render"); }
private:
};
#endif