#include "Menu.h"
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

void Menu::requestPassword(std::string &password)
{
	std::cout << "Unesite korisnicko ime:";
	std::cout << std::endl << "Unesite sifru:";
	std::cin >> password;
}