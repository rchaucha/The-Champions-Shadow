#ifndef DEF_STUN
#define DEF_STUN

#include "Effect.h"

class Stun : public Effect
{
public:
	Stun(Character* target, unsigned short nbr_of_rounds);
	~Stun();

	void apply() override;

	std::string getDescription(LangManager const *lang_manager) const override { return lang_manager->getStrById("stun_render"); }
private:

};
#endif