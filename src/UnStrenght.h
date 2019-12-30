#ifndef DEF_UNSTRENGHT
#define DEF_UNSTRENGHT

#include "Effect.h"

class UnStrenght : public Effect
{
public:
	UnStrenght(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~UnStrenght();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("unstrenght_render"); }
private:
};
#endif