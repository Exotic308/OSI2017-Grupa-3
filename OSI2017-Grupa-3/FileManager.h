#pragma once
#include <string>
#include <iostream>
#include <vector>
#pragma once
class FileManager
{
private:
	static std::string getexepath();
	static bool saveToFile(std::string, std::string);
public:
	static std::vector<std::string> GetPathsWithExtension(std::string ext, std::string relativePath);
	static bool saveToFolder(std::string, std::string, std::string);
};
