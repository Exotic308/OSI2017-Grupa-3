#include "FileManager.h"
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <direct.h>
namespace fs = std::experimental::filesystem;

std::string FileManager::getexepath()
{
	char result[MAX_PATH];
	int found;
	GetModuleFileName(NULL, result, MAX_PATH);
	found = std::string(result).find_last_of("\\");
	return(std::string(result).substr(0, found) + "\\");
}

std::vector<std::string> FileManager::GetPathsWithExtension(std::string ext, std::string relativePath)
{
	std::string path = getexepath();
	if (relativePath != "") path += relativePath + "\\";
	int counter = 0;
	for (auto & p : fs::directory_iterator(path)) {
		std::string s;
		s = p.path().string();
		std::string tempExt = s.substr(s.length() - 3, 3);
		if (tempExt == ext) ++counter;
	}
	std::vector<std::string> paths(counter);
	counter = 0;
	for (auto & p : fs::directory_iterator(path)) {
		std::string s;
		s = p.path().string();
		std::string tempExt = s.substr(s.length() - 3, 3);
		if (tempExt == ext) paths[counter++] = s;
	};
	return paths;
}

bool FileManager::saveToFolder(std::string directory, std::string filename, std::string text)
{
	std::string abs_path = getexepath() + directory;
	_mkdir(abs_path.c_str());
	return saveToFile(abs_path + "\\" + filename, text);
}

bool FileManager::saveToFile(std::string path, std::string text)
{
	std::ofstream myfile;
	myfile.open(path);
	myfile << text;
	myfile.close();
	return true;
}
