#pragma once
#include <iostream>
#include "JSONParser.hpp"
#include "Encryption.h"
using nlohmann::json;
class User
{
	bool admin;
	std::string pin;
	int decryptionKey;
public:
	std::string name;
	std::string surname;
	std::string username;
	std::string encryptedPin = "";

	User(std::string = "", std::string = "", std::string = "", std::string = "", bool = false);
	
	inline bool isAdmin() { return admin; }
	inline std::string getPin() { return pin; }

	std::string hasErrors();
	void encryptPin(Encryption&);
	std::string decryptKey(Encryption&);

	std::string getEncryptedJSON();
	void loadFromEncryptedJSON(std::string s);
};
