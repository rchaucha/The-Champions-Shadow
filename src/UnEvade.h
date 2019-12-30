#ifndef DEF_UNEVADE
#define DEF_UNEVADE

#include "Effect.h"

class UnEvade : public Effect
{
public:
	UnEvade(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~UnEvade();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("unevade_render"); }
private:
};
#endif