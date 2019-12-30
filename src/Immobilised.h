#ifndef DEF_IMMOBILISED
#define DEF_IMMOBILISED

#include "Effect.h"

class Immobilised : public Effect
{
public:
	Immobilised(Character* target, unsigned short nbr_of_rounds);
	~Immobilised();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("immobilized_render"); }
private:

};
#endif