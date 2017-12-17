#pragma once
#include <iostream>

class User
{
	bool admin;
	std::string pin;
public:
	std::string name;
	std::string surname;

	User(std::string, std::string, std::string, bool);
	
	inline bool isAdmin() { return admin; }

	std::string hasErrors();
};

