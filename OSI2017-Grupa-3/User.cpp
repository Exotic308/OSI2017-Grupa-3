#include "User.h"
#include <cctype>



User::User(std::string name, std::string surname, std::string username, std::string pin, bool admin) : name(name), surname(surname), username(username), pin(pin), admin(admin)
{}

std::string User::hasErrors()
{
	if (pin.length() != 4)
		return "0Duzina pin koda nije validna.";
	else
		for(int i = 0; i < pin.length(); i++)
			if (!isdigit(pin[i]))
				return "0Pin sadrzi karaktere koji nisu cifre.";
	return "1";
}

std::string User::encryptPin()
{
	if (!isPinEncrypted) {
		Encryption::xorEncryptDecrypt(pin);
		isPinEncrypted = true;
		return "1";
	}
	return "0Pin je vec enkriptovan.";
}

std::string User::decryptPin()
{
	if (isPinEncrypted) {
		Encryption::xorEncryptDecrypt(pin);
		isPinEncrypted = false;
		return "1";
	}
	return "0Pin nije enkriptovan.";
}

std::string User::getEncryptedJSON()
{
	json j = {
		{"name",name},
		{"surname",surname},
		{"username",username},
		{"admin",admin},
		{"pin", pin }
	};
	return Encryption::xorEncryptDecrypt(j.dump());
}
void User::loadFromEncryptedJSON(std::string s) {
	s = Encryption::xorEncryptDecrypt(s);
	json j = json::parse(s);
	name = j.at("name").get<std::string>();
	surname = j.at("surname").get<std::string>();
	username = j.at("username").get<std::string>();
	pin = j.at("pin").get<std::string>();
	admin = j.at("admin").get<bool>();
}

