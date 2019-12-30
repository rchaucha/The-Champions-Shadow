#ifndef DEF_PRECISION
#define DEF_PRECISION

#include "Effect.h"

class Precision : public Effect
{
public:
	Precision(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary, unsigned int effect_level = 0);
	~Precision();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("precision_render"); }
private:
};
#endif