#include "FilesManager.h"

#include <iostream>
#include <fstream>
#include <direct.h>
#include <Windows.h>
#include "tinyxml2.h"

using namespace std;

FilesManager::FilesManager() :
	_files_path("../../files")
{}

const string FilesManager::encryptDecrypt(string const to_encrypt) const
{
	string output = to_encrypt;

	char const key[10] = { 'K', 'C', 'Q', 'R', 'S', 'J', 'Z', 'A', 'P', 'L' };

	for (int i = 0; i < (int)to_encrypt.size(); i++)
	{
		output[i] = to_encrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
	return output;
}

void FilesManager::save() const
{
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!!
		FONCTION A MODIFIER
	!!!!!!!!!!!!!!!!!!!!!!!!!!!

	string file_path = _files_path + "/data/argent.txt";
	ofstream fichier_money(file_path.c_str(), ios::out | ios::trunc);
	if (fichier_money)
		fichier_money << "" << endl;
	else
		errorOpenFiles("argent.txt");*/
}

void FilesManager::reset() const
{
	/////////DOSSIERS//////////
	string lang_folder_path = _files_path + "/lang";
	string data_folder_path = _files_path + "/data";
	string pictures_folder_path = _files_path + "/pictures";
	string settings_folder_path = _files_path + "/settings";
	string sounds_folder_path = _files_path + "/sounds";

	CreateDirectory(wstring(_files_path.begin(), _files_path.end()).c_str(), NULL);					  //on crée le dossier files
	CreateDirectory(wstring(lang_folder_path.begin(), lang_folder_path.end()).c_str(), NULL);		  //on crée le dossier lang
	CreateDirectory(wstring(data_folder_path.begin(), data_folder_path.end()).c_str(), NULL);		  //on crée le dossier data
	CreateDirectory(wstring(pictures_folder_path.begin(), pictures_folder_path.end()).c_str(), NULL); //on crée le dossier pictures
	CreateDirectory(wstring(settings_folder_path.begin(), settings_folder_path.end()).c_str(), NULL); //on crée le dossier settings
	CreateDirectory(wstring(sounds_folder_path.begin(), sounds_folder_path.end()).c_str(), NULL);	  //on crée le dossier sounds


	/////////LANGUES//////////
		///////FR////////
	{
		string file_path = lang_folder_path + "/fr.txt";
		ofstream settings_file(file_path.c_str(), ios::out | ios::trunc);
		settings_file <<
			"game_presentation:         \\\\\\\\\\\\\\\\The Champions' Shadow////////\\nJOUER (1)\\nPARAMETRES (2)\\nQUITTER (3)\\n\\nVeuillez entrer le chiffre de l'action que vous souhaitez effectuer.\n" <<
			"choose_character:Veuillez choisir un personnage :\\nGuerrier(1)\\nPretre(2)\n" <<
			"choose_a_correct_number:Veuillez entrer un nombre correct.\n" <<
			"choose_pseudo:Quel sera votre pseudo ? (tapez 'auto' si vous n'etes pas inspire)\n" <<
			"character_chosen:Vous avez choisi %s %s\n" <<
			"ennemy_chosen:Vous combattrez contre %s %s\n" <<
			"display_life_point:Il reste %i points de vie a %s.\n" <<
			"choose_attack:Veuillez choisir une attaque :\n" <<
			"attack_unusable:(INUTILISABLE)\n" <<
			"attack_missed:L'attaque rate!\n" <<
			"evade:%s esquive l'attaque!\n" <<
			"attack_blocked:%s pare l'attaque!\n" <<
			"attack_failed1:%s glisse et son attaque rate!\n" <<
			"attack_failed2:%s est deconcentre et rate son attaque!\n" <<
			"attack_weakened1:%s tente d'esquiver mais l'attaque l'atteint tout de meme! Elle est cependant affaiblie.\n" <<
			"attack_weakened2:%s tente de devier l'attaque mais subit quelques degats. L'attaque est affaiblie.\n" <<
			"attack_weakened3:%s veut parer l'attaque mais la puissance de l'attaque le fait vaciller!L'attaque est cependant affaiblie.\n" <<
			"critical_hit1:%s est frappe de plein fouet!Coup critique!\n" <<
			"critical_hit2:%s n'a pas vu venir l'attaque!Coup critique!\n" <<
			"critical_hit3:La puissance de l'attaque est devastatrice! Coup critique!\n" <<
			"no_damage:La vie de %s reste intacte.\n" <<
			"stun_render:%s est etourdi, et ne pourra plus attaquer!\n" <<
			"exhausted_render:%s est epuise par l'attaque qu'il vient de faire, et ne pourra plus attaquer!\n" <<
			"immobilized_render:%s est immobilise, et ne peut pas attaquer!\n" <<
			"unattainable_render:%s est inaccessible et ne peut pas etre touche!\n" <<
			"weakness_render:%s est affaibli, et sa puissance d'attaque diminue!\n" <<
			"imprecision_render:%s est destabilise, et sa precision diminue!\n" <<
			"waning_render:La protection de %s est touchee, et sa defense baisse!\n" <<
			"unevade_render:%s est ralenti, et sa capacite a eviter les attaques diminue!\n" <<
			"regen_render:%s est entoure d'un aura magique, et voit sa vie remonter!\n" <<
			"strenght_render:%s sent son envie de combat augmenter, et sa puissance d'attaque avec!\n" <<
			"defense_render:%s voit son armure s'ameliorer, et devient plus resistant!\n" <<
			"precision_render:La vue de %s s'aiguise et reduit ses chances de rater sa cible!\n" <<
			"evade_render:%s se concentre sur %s et anticipe plus facilement ses mouvements pour les eviter!\n" <<
			"effect_level_render:Niveau de l'effet: %i.\n" <<
			"life_points_lost:%s a perdu %i points de vie!\n" <<
			"life_points_healed:%s a gagne %i points de vie!\n" <<
			"no_more_life_points:%s n'a plus de point de vie!\n" <<
			"you_win:Vous gagnez donc le combat!\n" <<
			"you_loose:Vous perdez donc le combat!\n" <<
			"too_exhausted_to_attack:%s est trop fatigue pour attaquer.\n" <<
			"warrior_name:le Guerrier\n" <<
			"cleric_name:le Pretre\n" <<
			"play:Jouer\n" <<
			"settings:Parametres\n" <<
			"miss_turn:Ne rien faire\n" <<
			"turn_missed_render:%s attend patiemment l'attaque de %s.\n" <<
			"mortal_hit_name:Frappe Mortelle\n" <<
			"defense_breaker_name:Brise - Defense\n" <<
			"provocation_name:Provocation\n" <<
			"mental_hurt_name:Souffrance Mentale\n" <<
			"dark_matter_name:Matiere Noire\n" <<
			"fourth_dimension_name:Quatrieme dimension\n" <<
			"first_aid_name:Premiers Secours\n" <<
			"mortal_hit_description:Frappe devastatrice mais necessitant un tour de repos.\n" <<
			"defense_breaker_description:Attaque peu puissance mais qui fait baisser durablement la defense adverse.\n" <<
			"provocation_description:Fait grandement baisser la precision adverse mais augmente son attaque.\n" <<
			"mental_hurt_description:Attaque classique.\n" <<
			"dark_matter_description:Votre adversaire est entoure de matiere invisible ce qui baisse sa precision et sa capacite a esquiver pendant 2 a 3 tours en plus de lui infliger quelques degats(cumulable).\n" <<
			"fourth_dimension_description:Votre adversaire est coince dans une dimension parallele, et ne peut pas attaquer ni etre attaque pendant 1 a 2 tours.\n" <<
			"first_aid_description:Vous vous soignez et regagnez entre 2 et 5 points de vie.";
	}

		///////EN////////
	{
		string file_path = lang_folder_path + "/en.txt";
		ofstream settings_file(file_path.c_str(), ios::out | ios::trunc);
		settings_file <<
			"game_presentation:         \\\\\\\\\\\\\\\\The Champions' Shadow////////\\nPLAY (1)\\nSETTINGS (2)\\nQUIT (3)\\n\\nPlease type the number corresponding to the action to make.\n" <<
			"choose_character:Please, choose a character :\\nWarrior (1)\\nCleric (2)\n" <<
			"choose_a_correct_number:Please, enter a correct number.\n" <<
			"choose_pseudo:Which pseudonym woud you like to use ? (type 'auto' if you're not inspired)\n" <<
			"character_chosen:You've chosen %s %s\n" <<
			"ennemy_chosen:You'll fight against %s %s\n" <<
			"display_life_point:There are %i life points remaining to %s.\n" <<
			"choose_attack:Please, choose an attack :\n" <<
			"attack_unusable:(UNUSABLE)\n" <<
			"attack_missed:The attack misses!\n" <<
			"evade:%s evade the attack!\n" <<
			"attack_blocked:%s block the attack!\n" <<
			"attack_failed1:%s slipped and his attack fails!\n" <<
			"attack_failed2:%s is distracted and fail his attack!\n" <<
			"attack_weakened1:%s tries to evade but the attack touch him anyway!However, it's weakened.\n" <<
			"attack_weakened2:%s tries to deflect the attack but take some damages.it's weakened.\n" <<
			"attack_weakened3:%s wants to block the attack, but its power makes him tooter!However, the attack is weakened.\n" <<
			"critical_hit1:%s is hitten really hard!Critical hit!\n" <<
			"critical_hit2:%s didn't see the attack coming! Critical hit!\n" <<
			"critical_hit3:The attack's power is devastating!Critical hit!\n" <<
			"no_damage:%s's life stay intact.\n" <<
			"stun_render:%s is stunned, and won't be able to attack for a while!\n" <<
			"exhausted_render:%s is exhausted by this attack, and won't be able to attack for a whileS!\n" <<
			"immobilized_render:%s is immobilized and can't attack.\n" <<
			"unattainable_render:%s is unattainable and can't be reached.\n" <<
			"unstrenght_render:%s is weakened, and his attack power decrease!\n" <<
			"unprecision_render:%s is destabilized, and his precision decrease !\n" <<
			"undefense_render:The %s's protection is weakened, and his precision decrease!\n" <<
			"unevade_render:%s is slowed, and his ability to evade decrease!\n" <<
			"regen_render:%s is circled by a magical aura, and see his life refilling!\n" <<
			"strenght_render:%s feels his desire for fight increasing along with his attack power!\n" <<
			"defense_render:%s see his armor strengthening. His defense increase!\n" <<
			"precision_render:The %s's sight sharpen, and decrease his chances to miss his target!\n" <<
			"evade_render:%s focus all his attention on his enemy, and anticipate more easily his moves to avoid them!\n" <<
			"effect_level_render:Effect level: %i.\n" <<
			"life_points_lost:%s loose %i life points!\n" <<
			"life_points_healed:%s healed %i life points!\n" <<
			"no_more_life_points:%s has no more life points !\n" <<
			"you_win:You win the fight!\n" <<
			"you_loose:You loose the fight!\n" <<
			"too_exhausted_to_attack:%s is too exhausted to attack.\n" <<
			"warrior_name:the Warrior\n" <<
			"cleric_name:the Cleric\n" <<
			"play:Play\n" <<
			"settings:Settings\n" <<
			"miss_turn:Do nothing.\n" <<
			"turn_missed_render:%s patiently waits %s's attack.\n" <<
			"mortal_hit_name:Mortal Hit\n" <<
			"defense_breaker_name:Defense-Breaker\n" <<
			"provocation_name:Provocation\n" <<
			"mental_hurt_name:Mental Hurt\n" <<
			"dark_matter_name:Dark Matter\n" <<
			"fourth_dimension_name:Fouth Dimension\n" <<
			"first_aid_name:First Aid\n" <<
			"mortal_hit_description:Devastating hit but needing a one-round break.\n" <<
			"defense_breaker_description:Not really strong attack, but decrease the ennemy defense.\n" <<
			"provocation_description:Greatly decrease ennemy precision but increase his attack power.\n" <<
			"mental_hurt_description:Basic attack.\n" <<
			"dark_matter_description:Your target is circled by invisible matter which decrease is ability to evade for 2 or 3 rounds, and inflict him a few damages (cumulable).\n" <<
			"fourth_dimension_description:Your target is stuck in a parallel dimension, and can't attack and neither be attacked for 1 or 2 rounds.\n" <<
			"fisrt_aid_description:You heal yourself and regen 2 to 5 life points.";
	}

	/////////SETTINGS//////////
	string file_path = settings_folder_path + "/settings.txt";

	ofstream settings_file(file_path.c_str(), ios::out | ios::trunc);
	settings_file << 
		"mode:text\n" <<
		"lang:fr\n" <<
		"reading_speed_coef:1";
}

map<string, string> FilesManager::getData(string file_path_from_files_directory) const
{
	map<string, string> return_map;

	string file_path = _files_path + "/" + file_path_from_files_directory;

	bool is_file_open_correctly = false;

	while (!is_file_open_correctly)
	{
		ifstream settings_file(file_path.c_str(), ios::in); //ouverture du fichier

		if (!settings_file.fail() && settings_file && (settings_file.peek() != ifstream::traits_type::eof())) //si fichier ouvert et complet
		{
			is_file_open_correctly = true;

			string line = "",
				key = "",
				value = "";

			while (getline(settings_file, line)) //on passe toutes les lignes
			{
				bool is_dot_passed = false;
				for (unsigned int i = 0; i < line.length(); ++i)
				{
					if (line[i] == ':') //si on a atteint ":"
					{
						is_dot_passed = true;
					}

					else if (!is_dot_passed) //si on est encore au premier mot
					{
						key += line[i];
					}

					else //si on a passé ":"
					{
						value += line[i];
					}
				}
				return_map[key] = value;
				key = value = "";
			}
		}
		else
		{
			errorOpenFiles(file_path);
		}
	}

	return return_map;
}

void FilesManager::errorOpenFiles(std::string const file_name)
{
	FilesManager files_manager;
	files_manager.reset();

	cout << "Le fichier " << file_name << " n'ayant pas pu etre ouvert lors de la lecture, les fichiers sont recrees. Si vous souhaitez changer les parametres par defaut, veuillez redemarrer le programme apres modifications." << endl;
	Sleep(2000);
}
