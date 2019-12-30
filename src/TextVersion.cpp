#include "TextVersion.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <cstdarg>
#include "FilesManager.h"

using namespace std;

TextVersion::TextVersion(Settings::Lang lang, float reading_speed_coef) : AbstractVersion(lang),
_reading_speed_coef(reading_speed_coef)
{}

TextVersion::MenuChoice TextVersion::displayMenu()
{
	int choice_i;
	cout << _lang_manager.getStrById("game_presentation") << endl;
	
	while (TRUE)
	{
		cin >> choice_i;

		switch (choice_i)
		{
		case 1:
			return MenuChoice::Play; break;
		case 2:
			return MenuChoice::Settings; break;
		case 3:
			return MenuChoice::Quit; break;
		default: break;
		}
	}
	return MenuChoice::Quit;
}

CharacterFactory::CharacterType TextVersion::chooseCharacter()
{
	CharacterFactory::CharacterType character = CharacterFactory::CharacterType::UndefinedType;
	bool is_char_chosen = false;

	while (!is_char_chosen)
	{
		is_char_chosen = true;

		string str_character;

		printf(_lang_manager.getStrById("choose_character").c_str());
		cin >> str_character;

		if (str_character == "1")
		{
			character = CharacterFactory::CharacterType::WarriorType;
		}
		else if (str_character == "2")
		{
			character = CharacterFactory::CharacterType::ClericType;
		}
		else
		{
			printf(_lang_manager.getStrById("choose_a_correct_number").c_str());
			is_char_chosen = false;
		}
	}

	printf("\n");

	return character;
}

string TextVersion::choosePseudo()
{
	string pseudo = "";

	printf(_lang_manager.getStrById("choose_pseudo").c_str());
	cin.ignore();
	getline(cin, pseudo);

	for (unsigned int i = 0; i < pseudo.length(); i++)
	{
		if (pseudo[i] == ' ')
			pseudo[i] = '_';
	}

	if (pseudo != "")
		printf("\n");

	return pseudo;
}

void TextVersion::displayPlayersPresentation(Character * const player, Character * const enemy)
{
	printf(_lang_manager.getStrById("character_chosen", 0).c_str(), player->getName().c_str(), player->getClassNameStr(&_lang_manager).c_str());
	_wait(750);
	printf(_lang_manager.getStrById("ennemy_chosen", 1).c_str(), enemy->getName().c_str(), enemy->getClassNameStr(&_lang_manager).c_str());
	_wait(1000);
}

void TextVersion::lifeDisplay(Character * const player, Character * const enemy)
{
	printf(_lang_manager.getStrById("display_life_point").c_str(), player->getLife(), player->getName().c_str());
	_wait(1000);
	printf(_lang_manager.getStrById("display_life_point", 2).c_str(), enemy->getLife(), enemy->getName().c_str());
	_wait(1000);
}

void TextVersion::manaDisplay(Character * const player)
{
	cout << "Mana : " << player->getMana() << endl << endl;
	_wait(1000);
}

unsigned short TextVersion::attackChoice(Character * const player, bool is_enemy_attainable)
{
	vector<string> attacks_list = player->getAttacksNameList(&_lang_manager); //liste de ses attaques
	map<string, string> attack_description_map = player->getAttacksDescription(&_lang_manager);

	printf(_lang_manager.getStrById("choose_attack", 2).c_str());

	_wait(500);

	cout << "Mana:" << endl;

	vector<unsigned int> unusable_attacks_id;
	string usable = "";
	shared_ptr<AAttackDefinition> current_attack;

	unsigned short id = 0;

	for (string attack_name : attacks_list)
	{
		usable = "";

		current_attack = player->getAttackById(id);

		unsigned short mana_consumption = current_attack->getManaConsumption();

		if ((!is_enemy_attainable && !current_attack->is_user_targeted_only()) || (player->getMana() < current_attack->getManaConsumption())) //si l'ennemi n'est pas accessible (4e dimension par ex) et que l'attaque le vise OU pas assez de mana => on la met dans la liste des interdites
		{
			unusable_attacks_id.push_back(id);
			usable = _lang_manager.getStrById("attack_unusable", 0) + " ";
		}

		string attack_description = attack_description_map[attack_name];
		cout << mana_consumption << "  :" << usable.c_str() << attack_name << " (" << id++ << ") : " << attack_description;
	}

	cout << "00" << "  :" << _lang_manager.getStrById("miss_turn", 0).c_str() << " (" << id << ")" << endl;

	unsigned short choice = 0;
	bool is_choice_valid = false;

	do		//Tant que le joueur n'a pas entré un nbr correct
	{
		string str_choice;
		cin >> str_choice;

		try
		{
			choice = (unsigned short)stoi(str_choice);
			is_choice_valid = true;
		}
		catch (invalid_argument)
		{
			is_choice_valid = false;
		}

		for (unsigned int i : unusable_attacks_id) //on regarde si le choix correspond à une attaque inutilisable
		{
			if (i == choice)
				is_choice_valid = false;
		}

		if (choice > player->getAttacksListSize() || !is_choice_valid)
		{
			printf(_lang_manager.getStrById("choose_a_correct_number").c_str());
			is_choice_valid = false;
		}
	} while (!is_choice_valid);

	printf("\n");

	_wait(500);

	return choice;
}

void TextVersion::turnMissed(Character * const player, Character * const target)
{
	printf(_lang_manager.getStrById("turn_missed_render", 2).c_str(), player->getName().c_str(), target->getName().c_str());
}

void TextVersion::renderLastAttack(std::vector<AttackSpecificity*> attack_specificity_vct)
{
	vector<string> attacks_already_rendered_list;
	bool is_already_rendered = false;

	for (AttackSpecificity* attack_specify_ptr : attack_specificity_vct)
	{
		string attack_id = attack_specify_ptr->getAttackNameId();

		is_already_rendered = false;

		for (string attack_already_rendered : attacks_already_rendered_list)
		{
			if (attack_id == attack_already_rendered) //si l'attaque était déjà affichée
				is_already_rendered = true;
		}

		if (!is_already_rendered) //si elle n'a pas encore été affichée, on l'affiche et on l'ajoute à la liste des affichées
		{
			attacks_already_rendered_list.push_back(attack_id);
			printf(_lang_manager.getStrById("attack_action_render").c_str(), attack_specify_ptr->getUser()->getName().c_str(), _lang_manager.getStrById(attack_id, 0).c_str());
		}

		_wait(1200);

		switch (attack_specify_ptr->getSkillType())
		{
		case AttackSpecificity::SkillType::DamageAttack:
			_renderDamageAttack(attack_specify_ptr); break;
		case AttackSpecificity::SkillType::EffectAttack:
			_renderEffectAttack(attack_specify_ptr); break;
		default: break;
		}
	}
	_wait(2000);
}

void TextVersion::_renderDamageAttack(AttackSpecificity* attack_specify_ptr) const
{
	unsigned int sentence = rand() % 3;

	int relative_life_change = attack_specify_ptr->getRelativeLifeChange();
	Character* user;
	Character* target;
	user = attack_specify_ptr->getUser();
	target = attack_specify_ptr->getTarget();

	unsigned int absolute_relative_life_change = 0;

	if (relative_life_change < 0) //Valeur absolue de relative_life_change
		absolute_relative_life_change = 0 - relative_life_change;
	else
		absolute_relative_life_change = relative_life_change;

	switch (attack_specify_ptr->getAttackSpeType())
	{
	case AttackSpecificity::AttackSpeType::Missed:
		switch (sentence)
		{
		case 0:
			printf(_lang_manager.getStrById("attack_missed").c_str());	break;
		case 1:
			printf(_lang_manager.getStrById("evade").c_str(), target->getName().c_str());	break;
		case 2:
			printf(_lang_manager.getStrById("attack_blocked").c_str(), target->getName().c_str());	break;
		default: break;
		} break;
	case AttackSpecificity::AttackSpeType::Failed:
		switch (sentence)
		{
		case 0:
			printf(_lang_manager.getStrById("attack_missed").c_str());	break;
		case 1:
			printf(_lang_manager.getStrById("attack_failed1").c_str(), user->getName().c_str());	break;
		case 2:
			printf(_lang_manager.getStrById("attack_failed2").c_str(), user->getName().c_str());	break;
		default: break;
		} break;
	case AttackSpecificity::AttackSpeType::Weakened:
		switch (sentence)
		{
		case 0:
			printf(_lang_manager.getStrById("attack_weakened1").c_str(), target->getName().c_str());	break;
		case 1:
			printf(_lang_manager.getStrById("attack_weakened2").c_str(), target->getName().c_str());	break;
		case 2:
			printf(_lang_manager.getStrById("attack_weakened3").c_str(), target->getName().c_str());	break;
		default: break;
		} break;
	case AttackSpecificity::AttackSpeType::CriticalHit:
		switch (sentence)
		{
		case 0:
			printf(_lang_manager.getStrById("critical_hit1").c_str(), target->getName().c_str());	break;
		case 1:
			printf(_lang_manager.getStrById("critical_hit2").c_str(), target->getName().c_str());	break;
		case 2:
			printf(_lang_manager.getStrById("critical_hit3").c_str(), target->getName().c_str());	break;
		default: break;
		}	break;
	default: break;
	}

	if (attack_specify_ptr->getAttackSpeType() != AttackSpecificity::AttackSpeType::Normal)
		_wait(2000);

	if (relative_life_change < 0)
		printf(_lang_manager.getStrById("life_points_lost", 2).c_str(), target->getName().c_str(), absolute_relative_life_change);
	else if (relative_life_change > 0)
		printf(_lang_manager.getStrById("life_points_healed", 2).c_str(), target->getName().c_str(), absolute_relative_life_change);
	else
		printf(_lang_manager.getStrById("no_damage", 2).c_str(), target->getName().c_str());
}

void TextVersion::_renderEffectAttack(AttackSpecificity* attack_specify_ptr) const
{
	Character* target = attack_specify_ptr->getTarget();

	unsigned int effect_level = attack_specify_ptr->getEffet()->getLevel();

	printf(attack_specify_ptr->getEffet()->getDescription(&_lang_manager).c_str(), target->getName().c_str());

	if (effect_level != 0)
	{
		_wait(1000);
		printf(_lang_manager.getStrById("effect_level_render").c_str(), effect_level);
	}

	printf("\n");
}

void TextVersion::death(Character * const player)
{
	printf(_lang_manager.getStrById("no_more_life_points").c_str(), player->getName().c_str());
}

void TextVersion::win()
{
	printf(_lang_manager.getStrById("you_win").c_str());

	_wait(3000);
}

void TextVersion::lose()
{
	printf(_lang_manager.getStrById("you_loose").c_str());

	_wait(3000);
}

void TextVersion::cantAttackRender(Character * const player)
{
	printf(_lang_manager.getStrById("cant_attack_render", 2).c_str(), player->getName().c_str());

	_wait(1500);
}

void TextVersion::_wait(unsigned int time) const
{
	if (time != 0) //si le coef vaut 0, on attend pas
	{
		time = unsigned int(time / _reading_speed_coef);
		Sleep(time);
	}
}

string TextVersion::_toLower(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}