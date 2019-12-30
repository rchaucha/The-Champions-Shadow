#include "Settings.h"

using namespace std;

Settings::Settings() :
	_settings_file_path("../files/settings"),
	_file_name("settings.txt")
{}

void Settings::readData(FilesManager *files_manager)
{
	_data_map = files_manager->getData(_settings_file_path + "/" + _file_name);

	applyData();
}

void Settings::applyData()
{
	////MODE DE JEU (Texte, 2D, ...)////
	{
		string str_mode = _data_map["mode"];

		if (str_mode == "text")
		{
			_mode = Mode::Text;
		}
		else if (str_mode == "pictures")
		{
			_mode = Mode::Pictures;
		}
		else
		{
			_mode = Mode::UndefinedMode;
		}
	}
	

	////LANGUE////
	{
		string str_lang = _data_map["lang"];

		if (str_lang == "fr")
		{
			_lang = Lang::fr;
		}
		else if (str_lang == "en")
		{
			_lang = Lang::en;
		}
		else
		{
			_lang = Lang::UndefinedLang;
		}
	}
	

	////VITESSE DE LECTURE (pour mode texte)////
	{
		string str_reading_speed = _data_map["reading_speed_coef"];

		try
		{
			_reading_speed_coef = stof(str_reading_speed);

			if (_reading_speed_coef < 0)
				throw invalid_argument("Coefficient negatif");
		}
		catch (...)
		{
			_reading_speed_coef = 1;
		}
	}
}