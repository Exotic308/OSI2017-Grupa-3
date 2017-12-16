#include "Menu.h"

void Menu::requestPassword(std::string &password)
{
	std::cout << "Unesite korisnicko ime:";
	std::cout << std::endl << "Unesite sifru:";
	std::cin >> password;
}