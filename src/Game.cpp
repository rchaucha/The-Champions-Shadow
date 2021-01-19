#include "Game.h"

#include <time.h>
#include <memory>
#include <filesystem>
#include <Windows.h>
#include "Character.h"
#include "AbstractVersion.h"

using namespace std;

Game::Game() :
	_is_game_closed(false),
	_player(nullptr),
	_ai(nullptr)
{}

void Game::init()
{
	srand((unsigned int)time(0));
	_settings.readData(&_files_manager);
	_version.reset(new VersionsManager(_settings.getMode(), _settings.getLang(), _settings.getReadingSpeedCoef()));
}

Game::~Game()
{
	delete _player;
	_player = nullptr;

	delete _ai;
	_ai = nullptr;
}

void Game::launch()
{
	AbstractVersion::MenuChoice menu_choice = _version->displayMenu();

	switch (menu_choice)
	{
	case AbstractVersion::MenuChoice::Play:
	{
		CharacterFactory::CharacterType character_chosen = _version->chooseCharacter();
		string pseudo = _version->choosePseudo();

		_character_factory.characterCreater(&_player, "", pseudo, character_chosen);	//Creation des deux personnages
		_character_factory.characterCreater(&_ai, _player->getName());

		_version->displayPlayersPresentation(_player, _ai);
			
		_play();
		break;
	}
	case AbstractVersion::MenuChoice::Settings:
	{
		string settings_path = getFilesPath() + "/settings/settings.txt";

		ShellExecute(NULL, L"open", stringToWstring(settings_path).c_str(), NULL, NULL, SW_SHOWDEFAULT);

		return;
	}
	case AbstractVersion::MenuChoice::Quit:
		_is_game_closed = true;
		return;
	default:
		break;
	}
}

void Game::_play()
{
	while (!_is_game_closed)
	{
		_version->lifeDisplay(_player, _ai);
		_version->manaDisplay(_player);

		_playerAttack();

		_updateEffects(_ai);

		if (_ai->getLife() <= 0)
		{
			_aiDead();
			break;
		}

		_aiAttack();

		_updateEffects(_player);

		if (_player->getLife() <= 0)
		{
			_playerDead();
			break;
		}

		_updateMana();
	}
}

void Game::_playerAttack()
{
	if (_player->canAttack())
	{
		unsigned short attack_id = _version->attackChoice(_player, _ai->canBeAttacked());

		if (attack_id < _player->getAttacksListSize()) //si le choix de l'attaque n'est pas compris dans la taille de la liste des attaques, on n'attaque pas
		{
			shared_ptr<AAttackDefinition> attack_definition = _player->getAttackById(attack_id);

			_attack(_player, _ai, attack_definition);
		}
		else
			_version->turnMissed(_player, _ai);
	}
	else
		_version->cantAttackRender(_player);
}

void Game::_aiAttack()
{
	if (_ai->canAttack())
	{
		shared_ptr<AAttackDefinition> attack_definition = _ai->aiAction(*_player);

		_attack(_ai, _player, attack_definition);
	}
	else
		_version->cantAttackRender(_ai);
}

void Game::_attack(Character * const user, Character * const target, shared_ptr<AAttackDefinition> attack_definition)
{
	attack_definition->apply(user, target);

	_version->renderLastAttack(attack_definition->getAttackSpecificity());

	attack_definition->reset();
}

void Game::_updateEffects(Character * const target)
{
	target->updateEffects();
}

void Game::_updateMana()
{
	_player->addMana(rand() % (35 - 15) + 15);
	_ai->addMana(rand() % (35 - 15) + 15);
}

void Game::_playerDead()
{
	_version->death(_player);
	_version->lose();
	_is_game_closed = true;
}

void Game::_aiDead()
{
	_version->death(_ai);
	_version->win();
	_is_game_closed = true;
}

string Game::getFilesPath() const
{
	string files_dir = filesystem::current_path().parent_path().parent_path().u8string() + "/files";

	return files_dir;
}

std::wstring Game::stringToWstring(const std::string & s) const
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
