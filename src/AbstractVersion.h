#ifndef DEF_ABSTACTVERSION
#define DEF_ABSTACTVERSION

#include <vector>
#include "AttackSpecificity.h"
#include "CharacterFactory.h"
#include "Character.h"
#include "LangManager.h"
#include "Settings.h"

class AbstractVersion
{
public:
	enum MenuChoice { Play, Settings, Quit };

	AbstractVersion(Settings::Lang lang) :
		_lang(lang),
		_lang_manager(lang)
	{}

	virtual ~AbstractVersion() {}

	virtual MenuChoice displayMenu() = 0;
	virtual CharacterFactory::CharacterType chooseCharacter() = 0;
	virtual std::string choosePseudo() = 0;
	virtual void displayPlayersPresentation(Character * const player, Character * const enemy) = 0;
	virtual void lifeDisplay(Character * const player, Character * const enemy) = 0;
	virtual void manaDisplay(Character * const player) = 0;
	virtual unsigned short attackChoice(Character * const player, bool is_enemy_attainable) = 0;
	virtual void turnMissed(Character * const player, Character * const target) = 0;

	virtual void renderLastAttack(std::vector<AttackSpecificity*> attack_definition) = 0;
	virtual void death(Character * const player) = 0;
	virtual void win() = 0;
	virtual void lose() = 0;
	virtual void cantAttackRender(Character * const player) = 0;

protected:
	Settings::Lang _getLang() { return _lang; }
	LangManager _lang_manager;

private:
	Settings::Lang _lang;
};

#endif