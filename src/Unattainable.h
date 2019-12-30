#ifndef DEF_UNATTAINABLE
#define DEF_UNATTAINABLE

#include "Effect.h"

class Unattainable : public Effect
{
public:
	Unattainable(Character* target, unsigned short nbr_of_rounds);
	~Unattainable();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("unattainable_render"); }
private:

};
#endif