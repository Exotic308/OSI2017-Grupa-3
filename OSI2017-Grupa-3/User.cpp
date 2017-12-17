#include "User.h"
#include <cctype>



User::User(std::string name, std::string surname, std::string pin, bool admin) : name(name), surname(surname), pin(pin), admin(admin)
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

void to_json(nlohmann::json& j, const User& u)
{
	j = { {"name",u.name},{"surname",u.surname},{"admin",u.admin} };
}

void from_json(const nlohmann::json& j, User& u)
{
	u.name = j.at("name").get<std::string>();
	u.surname = j.at("surname").get<std::string>();
	u.admin = j.at("admin").get<bool>();
}
