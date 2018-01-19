#pragma once
#include "User.h"
#include <fstream>
#include "JSONParser.hpp"
#include <string>

using nlohmann::json;

class Users
{
	int count, capacity;
	User* users;
public:
	Users();
	~Users();

	std::string addUser(std::string name, std::string surname);
	std::string addUser();
	std::string loginUser(std::string username, std::string pin, User& user);
	std::string deleteUser(std::string username);
	json getJSON();
	void loadFromJSON(const json);
private:
	void capacityCheck();
	bool userAlreadyExists(std::string username, std::string pin);
	bool userAlreadyExists(std::string username);
};

