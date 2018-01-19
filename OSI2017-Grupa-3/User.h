#pragma once
#include <iostream>
#include "JSONParser.hpp"
#include "Encryption.h"

using nlohmann::json;

class User
{
	bool admin;
	std::string pin;
public:
	std::string name;
	std::string surname;
	std::string username;

	User(std::string = "", std::string = "", std::string = "", std::string = "", bool = false);
	
	inline bool isAdmin() { return admin; }
	inline std::string getPin() { return pin; }

	std::string hasErrors();
	std::string encryptPin();
	std::string decryptPin();

	std::string getEncryptedJSON();
	void loadFromEncryptedJSON(std::string s);
private:
	bool isPinEncrypted = false;
};
