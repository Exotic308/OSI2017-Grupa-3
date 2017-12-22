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

void User::encryptPin(Encryption& crypto)
{
	crypto.encrypt(pin);
	encryptedPin = crypto.encryptedMessage;
	decryptionKey = crypto.getKey();
}

std::string User::decryptKey(Encryption& crypto)
{
	return crypto.decrypt(decryptionKey);
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
	json j = s;
	name = j.at("name").get<std::string>();
	surname = j.at("surname").get<std::string>();
	username = j.at("username").get<std::string>();
	pin = j.at("pin").get<std::string>();
	admin = j.at("admin").get<bool>();
}

