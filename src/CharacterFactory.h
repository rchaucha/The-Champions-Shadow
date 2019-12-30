#ifndef DEF_CHARACTERFACTORY
#define DEF_CHARACTERFACTORY

#include <string>
#include <memory>

class Character;

class CharacterFactory
{
public:
	enum CharacterType { WarriorType, ClericType, UndefinedType };

	CharacterFactory();

	void characterCreater(Character** player, std::string const other_pseudo = "", std::string name = "", CharacterType character_type = CharacterType::UndefinedType) const;

private:
	const std::string _nameGenerator(CharacterType const character_type, std::string const other_pseudo = "") const;

};

#endif