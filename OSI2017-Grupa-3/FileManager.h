#include <string>
#include <iostream>
#include <vector>
#pragma once
class FileManager
{
	private:
		static std::string getexepath();
public:
	static std::vector<std::string> GetPathsWithExtension(std::string ext, std::string relativePath);
	FileManager();
	~FileManager();
};

