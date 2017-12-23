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

	std::string addUser(std::string, std::string, std::string);
	std::string loginUser(std::string, std::string, User& user);
	std::string deleteUser(std::string);
	void saveUsers();
	json getJSON();
	void loadFromJSON(const json);
private:
	void capacityCheck();
	bool userAlreadyExists(std::string, std::string);
	bool userAlreadyExists(std::string);
};

