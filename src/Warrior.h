#ifndef DEF_WARRIOR
#define DEF_WARRIOR

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "FilesManager.h"
#include "Character.h"
#include "AAttackDefinition.h"
#include "LangManager.h"
#include "AttackSpecificity.h"

class Warrior :public Character
{
public:
   Warrior(std::string name);

   const std::string getClassNameStr(LangManager const *lang_manager) const override { return lang_manager->getStrById("warrior_name"); }

   std::shared_ptr<AAttackDefinition> aiAction(Character const &enemy) const override;
};

#endif