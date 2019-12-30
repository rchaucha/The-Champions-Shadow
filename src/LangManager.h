#ifndef DEF_LANGMANAGER
#define DEF_LANGMANAGER

#include <string>
#include "Settings.h"
#include "FilesManager.h"

class LangManager
{
public:
   LangManager(Settings::Lang lang);

   const std::string getStrById(std::string const id, unsigned short nbr_lignes_returned = 1) const;

private:
   std::string const _lang_path;
   std::string _lang_file_name;
};

#endif