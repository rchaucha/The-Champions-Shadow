#ifndef DEF_UNPRECISION
#define DEF_UNPRECISION

#include "Effect.h"

class UnPrecision : public Effect
{
public:
	UnPrecision(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~UnPrecision();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("unprecision_render"); }
private:
};
#endif