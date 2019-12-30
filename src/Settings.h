#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <string>
#include <fstream>
#include <direct.h>
#include <iostream>
#include <map>
#include "SFML\graphics.hpp"
#include "FilesManager.h"

class Settings
{
public:
   enum Mode { Text, Pictures, UndefinedMode };
   enum Lang { fr, en, UndefinedLang };

   Settings();

   Mode getMode() { return _mode; }
   Lang getLang() { return _lang; }
   float getReadingSpeedCoef() { return _reading_speed_coef; }

   void readData(FilesManager *files_manager);
   void applyData();

private:
   Mode _mode;
   Lang _lang;
   float _reading_speed_coef;

   std::string _settings_file_path,
	  _file_name;
   std::map<std::string, std::string> _data_map;
};

#endif