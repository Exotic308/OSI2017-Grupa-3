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
