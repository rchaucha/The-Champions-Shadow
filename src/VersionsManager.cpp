#include "VersionsManager.h"
#include "Character.h"

using namespace std;

VersionsManager::VersionsManager(Settings::Mode mode, Settings::Lang lang, float reading_speed_coef) : AbstractVersion(lang),
_mode(mode),
_text(nullptr),
_pic(nullptr)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text = new TextVersion(lang, reading_speed_coef); break;
	case Settings::Mode::Pictures:
		_pic = new PicVersion(lang); break;
	default:
		break;
	}
}

VersionsManager::~VersionsManager()
{
	delete _text;
	_text = nullptr;

	delete _pic;
	_pic = nullptr;
}

AbstractVersion::MenuChoice VersionsManager::displayMenu()
{
	MenuChoice choice;

	switch (_mode)
	{
	case Settings::Mode::Text:
		choice = _text->displayMenu(); break;
	case Settings::Mode::Pictures:
		choice = _pic->displayMenu(); break;
	default:
		break;
	}

	return choice;
}

CharacterFactory::CharacterType VersionsManager::chooseCharacter()
{
	CharacterFactory::CharacterType character = CharacterFactory::CharacterType::UndefinedType;
	switch (_mode)
	{
	case Settings::Mode::Text:
		character = _text->chooseCharacter();
		break;
	case Settings::Mode::Pictures:
		character = _pic->chooseCharacter();
		break;
	default:
		break;
	}

	return character;
}

string VersionsManager::choosePseudo()
{
	string pseudo = "";

	switch (_mode)
	{
	case Settings::Mode::Text:
		pseudo = _text->choosePseudo();
		break;
	case Settings::Mode::Pictures:
		pseudo = _pic->choosePseudo();
		break;
	default:
		break;
	}

	return pseudo;
}

void VersionsManager::displayPlayersPresentation(Character * const player, Character * const ai)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->displayPlayersPresentation(player, ai); break;
	case Settings::Mode::Pictures:
		_pic->displayPlayersPresentation(player, ai); break;
	default: break;
	}
}

void VersionsManager::lifeDisplay(Character * const player, Character * const ai)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->lifeDisplay(player, ai); break;
	case Settings::Mode::Pictures:
		_pic->lifeDisplay(player, ai); break;
	default:
		break;
	}
}

void VersionsManager::manaDisplay(Character * const player)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->manaDisplay(player); break;
	case Settings::Mode::Pictures:
		_pic->manaDisplay(player); break;
	default:
		break;
	}
}

unsigned short VersionsManager::attackChoice(Character * const player, bool is_enemy_attainable)
{
	unsigned short choice = 0;

	switch (_mode)
	{
	case Settings::Mode::Text:
		choice = _text->attackChoice(player, is_enemy_attainable); break;
	case Settings::Mode::Pictures:
		choice = _pic->attackChoice(player, is_enemy_attainable); break;
	default:
		break;
	}

	return choice;
}

void VersionsManager::turnMissed(Character * const player, Character * const target)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->turnMissed(player, target); break;
	case Settings::Mode::Pictures:
		_pic->turnMissed(player, target); break;
	default:
		break;
	}
}

void VersionsManager::renderLastAttack(std::vector<AttackSpecificity*> attack_specificity_vct)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->renderLastAttack(attack_specificity_vct); break;
	case Settings::Mode::Pictures:
		_pic->renderLastAttack(attack_specificity_vct); break;
	default:
		break;
	}
}

void VersionsManager::death(Character * const player)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->death(player); break;
	case Settings::Mode::Pictures:
		_pic->death(player); break;
	default:
		break;
	}
}

void VersionsManager::win()
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->win(); break;
	case Settings::Mode::Pictures:
		_pic->win(); break;
	default:
		break;
	}
}

void VersionsManager::lose()
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->lose(); break;
	case Settings::Mode::Pictures:
		_pic->lose(); break;
	default:
		break;
	}
}

void VersionsManager::cantAttackRender(Character * const player)
{
	switch (_mode)
	{
	case Settings::Mode::Text:
		_text->cantAttackRender(player); break;
	case Settings::Mode::Pictures:
		_pic->cantAttackRender(player); break;
	default:
		break;
	}
}