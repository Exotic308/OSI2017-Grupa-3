#pragma once
#include <iostream>
#include "JSONParser.hpp"
#include "Encryption.h"

class User
{
	bool admin;
	std::string pin;
	int decryptionKey;
public:
	std::string name;
	std::string surname;
	std::string encryptedPin = "";

	User(std::string, std::string, std::string, bool);
	
	inline bool isAdmin() { return admin; }

	std::string hasErrors();
	void encryptPin(Encryption&);
	std::string decryptKey(Encryption&);
private:
	friend void to_json(nlohmann::json&, const User&);
	friend void from_json(const nlohmann::json&, User&);
};
