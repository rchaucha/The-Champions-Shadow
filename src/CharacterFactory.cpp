#include "CharacterFactory.h"
#include "Character.h"
#include "Warrior.h"
#include "Cleric.h"

using namespace std;

CharacterFactory::CharacterFactory()
{}

void CharacterFactory::characterCreater(Character** player, string const other_pseudo, string name, CharacterType character_type) const
{
	if (character_type == UndefinedType) //si la classe du perso n'a pas été définie
	{
		int random_char = rand() % 2; //choisi un personnage aléatoire

		switch (random_char)
		{
		case 0:
			character_type = WarriorType;
			break;
		case 1:
			character_type = ClericType;
			break;
		default:
			break;
		}
	}

	if (name == "") //si le nom du perso n'a pas été défini
	{
		name = _nameGenerator(character_type, other_pseudo);
	}

	switch (character_type)
	{
	case CharacterType::WarriorType:
		*player = new Warrior(name);
		break;
	case CharacterType::ClericType:
		*player = new Cleric(name);
		break;
	default:
		break;
	}
}

const string CharacterFactory::_nameGenerator(CharacterType const character_type, string const other_pseudo) const
{
	string name = "";
	int random_name = 0;

	vector<std::string> warrior_names;
	warrior_names.push_back("Vorzog");
	warrior_names.push_back("Kourk");
	warrior_names.push_back("Kalibor");
	warrior_names.push_back("Vrinmour");
	warrior_names.push_back("Korll");
	warrior_names.push_back("Soror");

	vector<std::string> cleric_names;
	cleric_names.push_back("Runvas");
	cleric_names.push_back("Ythas");
	cleric_names.push_back("Sirionne");
	cleric_names.push_back("Piyse");
	cleric_names.push_back("Utemianne");
	cleric_names.push_back("Hanin");

	do
	{
		switch (character_type)
		{
		case CharacterType::WarriorType:
			random_name = rand() % warrior_names.size();
			name = warrior_names[random_name];
			break;
		case CharacterType::ClericType:
			random_name = rand() % cleric_names.size();
			name = cleric_names[random_name];
			break;
		default:
			break;
		}
	} while (name == other_pseudo);

	return name;
}