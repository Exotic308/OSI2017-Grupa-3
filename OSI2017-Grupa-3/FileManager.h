#pragma once
#include <string>
#include <iostream>
#include <vector>
#pragma once
class FileManager
{
public:
	static std::string getexepath(); // funkcija koja trazi i vraca kao rezultat lokaciju programa
	static bool saveToFile(std::string, std::string); // funkcija sa opcijom da sacuva fajl u odgovarajuci direktorijum
	static std::vector<std::string> GetPathsWithExtension(std::string ext, std::string relativePath = ""); //funkcija koja trazi sve fajlove u odovarajucem direktorijumu sa trazenom ekstenzijom
	static bool saveToFolder(std::string, std::string, std::string); // funkcija koja cuva odg. tekst u odg. fajl u odg. direktorijum
};
