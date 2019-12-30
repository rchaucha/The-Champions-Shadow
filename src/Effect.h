#ifndef DEF_EFFECT
#define DEF_EFFECT

#include <memory>
#include <string>
#include "LangManager.h"

class Character;

class Effect
{
public:
	Effect(Character* target, unsigned short nbr_of_rounds, bool is_applicable_at_every_turn, bool is_temporary = true, unsigned int effect_level = 0) :
		_target(target),
		_initial_nbr_of_rounds(nbr_of_rounds),
		_nbr_of_rounds_remaining(nbr_of_rounds),
		_is_applicable_at_every_turn(is_applicable_at_every_turn),
		_is_temporary(is_temporary),
		_effect_level(effect_level),
		_is_first_turn_passed(false)
	{}

	virtual ~Effect() {}

	bool isFinished() const { return (_nbr_of_rounds_remaining <= 0) ? true : false; }
	void oneRoundPassed() { _nbr_of_rounds_remaining--; }

	virtual void apply() = 0;

	virtual std::string getDescription(LangManager const *lang_manager) const = 0;
	unsigned int getLevel() const { return _effect_level; }

protected:
	unsigned short _nbr_of_rounds_remaining;
	const unsigned short _initial_nbr_of_rounds;
	unsigned int _effect_level;
	bool _is_first_turn_passed;
	bool _is_applicable_at_every_turn;
	bool _is_temporary;

	Character* _target;
};

#endif