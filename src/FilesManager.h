#ifndef DEF_FILESMANAGER
#define DEF_FILESMANAGER

#include <string>
#include <map>

class FilesManager
{
public:
	FilesManager();
	const std::string encryptDecrypt(std::string const to_encrypt) const;
	void save()	   const;
	std::map<std::string, std::string> getData(std::string file_path_from_files_directory) const;
	void reset()   const;
	static void errorOpenFiles(std::string const file_name);

protected:
	std::string const _files_path;
};

#endif