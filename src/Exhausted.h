#ifndef DEF_EXHAUSTED
#define DEF_EXHAUSTED

#include "Effect.h"

class Exhausted : public Effect
{
public:
	Exhausted(Character* target, unsigned short nbr_of_rounds);
	~Exhausted();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("exhausted_render"); }
private:

};
#endif