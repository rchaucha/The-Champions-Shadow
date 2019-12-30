#include <string>
#include <iostream>
#include <limits>
#include <fstream>

using namespace std;

int main()
{
	bool is_finished = false;
	while (!is_finished)
	{
		string file_name = "";

		cout << "Nom du fichier relatif a 'files': (ex: 'lang/fr.txt', 'lang/en.txt', ...)" << endl;
		cin >> file_name;

		string line = "",
			return_code = "",
			files_path = "../../files/";

		string file_path = files_path + file_name;

		ifstream lang_file(file_path.c_str(), ios::in); //ouverture du fichier

		if (lang_file && (lang_file.peek() != ifstream::traits_type::eof())) //si fichier ouvert et complet
		{
			while (getline(lang_file, line)) //on passe toutes les lignes
			{
				return_code += ("\"" + line + "\\n\" <<\n");
			}

			for(int i = 0; i != 7; i++)
				return_code.pop_back();

			return_code += "\";";

			string file_path = "output.txt";
			ofstream file_stream(file_path.c_str(), ios::out | ios::trunc);
			file_stream << return_code;

			is_finished = true;
		}
		else
		{
			cout << "Erreur lors de l'ouverture de " << file_path << endl;
		}
	}

	return EXIT_SUCCESS;
}