#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class FileManager
{
public:
	static std::string getexepath(); 
	static bool saveToFile(std::string, std::string); 
	static std::vector<std::string> GetPathsWithExtension(std::string ext, std::string relativePath = ""); 
	static bool saveToFolder(std::string, std::string, std::string);
	static std::string getStringFromFile(const char * path);
};
