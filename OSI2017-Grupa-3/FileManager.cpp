#include "FileManager.h"
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <direct.h>
namespace fs = std::experimental::filesystem;

/*Funkcija koja trazi i vraca kao rezultat lokaciju programa.*/
std::string FileManager::getexepath()
{
	char result[MAX_PATH];
	int found;
	GetModuleFileName(NULL, result, MAX_PATH);
	found = std::string(result).find_last_of("\\");
	return(std::string(result).substr(0, found) + "\\");
}

/*Funkcija koja trazi sve fajlove u odovarajucem direktorijumu sa trazenom ekstenzijom.*/
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

/*Funkcija sa opcijom da sacuva fajl u odgovarajuci direktorijum.*/
bool FileManager::saveToFolder(std::string directory, std::string filename, std::string text)
{
	std::string abs_path = getexepath() + directory;
	_mkdir(abs_path.c_str());
	return saveToFile(abs_path + "\\" + filename, text);
}

/*Funkcija koja cuva odgovarajuci tekst u odgovarajuci fajl u odgovarajuci direktorijum*/
bool FileManager::saveToFile(std::string path, std::string text)
{
	std::ofstream myfile;
	myfile.open(path);
	myfile << text;
	myfile.close();
	return true;
}

/*Funkcija koja ucitava sadrzaj datoteke u obliku string-a.*/
std::string FileManager::getStringFromFile(const char * path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str() + "\n";
}

std::string FileManager::SplitFilename(std::string str)
{
	std::cout << "Splitting: " << str << '\n';
	std::size_t found = str.find_last_of("/\\");
	std::string ret = str.substr(found + 1);
	return ret;
}


