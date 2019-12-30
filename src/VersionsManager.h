#ifndef DEF_VERSIONSMANAGER
#define DEF_VERSIONSMANAGER

#include <string>
#include <typeinfo>
#include <memory>
#include <vector>
#include "AttackSpecificity.h"
#include "Settings.h"
#include "PicVersion.h"
#include "TextVersion.h"

class Character;

class VersionsManager :public AbstractVersion
{
public:
   VersionsManager(Settings::Mode, Settings::Lang, float reading_speed_coef = 1);
   ~VersionsManager();

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
   Settings::Mode _mode;

   TextVersion *_text;
   PicVersion *_pic;
};

#endif