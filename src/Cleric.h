#ifndef DEF_CLERIC
#define DEF_CLERIC

#include <string>
#include <map>
#include <vector>
#include "FilesManager.h"
#include "AAttackDefinition.h"
#include "Character.h"
#include "LangManager.h"

class Cleric :public Character
{
public:
	Cleric(std::string name);

	const std::string getClassNameStr(LangManager const *lang_manager) const { return lang_manager->getStrById("cleric_name"); }

	std::shared_ptr<AAttackDefinition> aiAction(Character const &enemy) const;
};

#endif