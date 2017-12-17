#pragma once
#include <iostream>
#include "JSONParser.hpp"

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
private:
	friend void to_json(nlohmann::json&, const User&);
	friend void from_json(const nlohmann::json&, User&);
};
