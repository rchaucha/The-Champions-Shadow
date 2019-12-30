#include "LangManager.h"

#include <limits>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

LangManager::LangManager(Settings::Lang lang) :
_lang_path("../../files/lang")
{
   switch (lang)
   {
   case Settings::Lang::fr:
	  _lang_file_name = "fr.txt"; break;
   case Settings::Lang::en:
	  _lang_file_name = "en.txt"; break;
   default:
	  _lang_file_name = "unknown"; break;
	  break;
   }
}

const string LangManager::getStrById(string const id, unsigned short nbr_lignes_returned) const
{
   string line = "",
	  key = "",
	  value = "";

   string file_path = _lang_path + "/" + _lang_file_name;

   bool is_file_open_correctly = false;

   while (!is_file_open_correctly)
   {
	  ifstream lang_file(file_path.c_str(), ios::in); //ouverture du fichier

	  if (lang_file && (lang_file.peek() != ifstream::traits_type::eof())) //si fichier ouvert et complet
	  {
		 is_file_open_correctly = true;

		 bool is_id_found = false;

		 while (getline(lang_file, line) && !is_id_found) //on passe toutes les lignes tant que l'ID n'est pas trouvé
		 {
			for (unsigned int i = 0; i < line.length(); ++i)
			{
			   if (line[i] == ':') //si on a atteint ":"
			   {
				  if (key == id) //si la clé est bien celle du msg que l'on veut obtenir, on enregistre le message
				  {
					 i++; //on ajoute 1 pour sauter les :
					 for (i; i < line.length(); ++i)
					 {
						value += line[i];
					 }
				  }
				  else //sinon, on passe à la ligne suivante
				  {
					 key = "";
					 break;
				  }
			   }
			   else //si on est encore au premier mot
			   {
				  key += line[i];
			   }
			}
		 }
	  }
	  else
	  {
		 FilesManager::errorOpenFiles(_lang_file_name);
	  }
   }

   for (nbr_lignes_returned; nbr_lignes_returned > 0; nbr_lignes_returned--)
	  value += "\n";

   return regex_replace(value, regex(R"(\\n)"), "\n");
}