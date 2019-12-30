#ifndef DEF_TEXTVERSION
#define DEF_TEXTVERSION

#include <string>
#include <vector>
#include "AttackSpecificity.h"
#include "IAttackDefinition.h"
#include "CharacterFactory.h"
#include "Character.h"
#include "AbstractVersion.h"
#include "LangManager.h"
#include "Settings.h"

class TextVersion :public AbstractVersion
{
public:
	TextVersion(Settings::Lang lang, float reading_speed_coef);
	AbstractVersion::MenuChoice displayMenu() override;
	CharacterFactory::CharacterType chooseCharacter() override;
	std::string choosePseudo() override;
	void displayPlayersPresentation(Character * const player, Character * const enemy) override;
	void lifeDisplay(Character * const player, Character * const enemy) override;
	void manaDisplay(Character * const player) override;
	unsigned short attackChoice(Character * const player, bool is_enemy_attainable) override;
	void turnMissed(Character * const player, Character * const target) override;

	void renderLastAttack(std::vector<AttackSpecificity*> attack_definition) override;
	void death(Character * const player) override;
	void win() override;
	void lose() override;
	void cantAttackRender(Character * const player) override;

private:
	void _renderDamageAttack(AttackSpecificity* attack_specify_ptr) const;
	void _renderEffectAttack(AttackSpecificity* attack_specify_ptr) const;
	void _wait(unsigned int time) const;
	static std::string _toLower(std::string str);

	float _reading_speed_coef;
};

#endif