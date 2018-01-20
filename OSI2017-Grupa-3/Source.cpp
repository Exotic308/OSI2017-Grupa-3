//потребно за унос или приказ података
#include <iostream>
#include "Message.h"
#include "InvoiceParser.h"
#include "Invoice.h"
#include "Users.h"
#include "InvoiceManager.h"
#include"Menu.h"
#include <vector>

//Почетни портал
void main() {
	std::cout << "Pocetni portal projektnog zadatka OSI2017-Grupa-3" << std::endl;
	std::string path = FileManager::getexepath();
	std::cout << path << std::endl;
	InvoiceManager main_manager; 
	Users users;
	Menu::UserUI(main_manager, &users);
	FileManager::saveToFolder("Users", "users.txt", (users.getJSON()).dump());
}