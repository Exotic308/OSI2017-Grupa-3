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

void to_json(nlohmann::json& j, const User& u)
{
	j = { {"name",u.name}, {"surname",u.surname}, {"username",u.username}, {"admin",u.admin} };
}

void from_json(const nlohmann::json& j, User& u)
{
	u.name = j.at("name").get<std::string>();
	u.surname = j.at("surname").get<std::string>();
	u.username = j.at("username").get<std::string>();
	u.admin = j.at("admin").get<bool>();
}
