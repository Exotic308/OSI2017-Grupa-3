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

	//Тестирање уноса рачуна
	
	std::string path = FileManager::getexepath();
	std::cout << path << std::endl;
	InvoiceManager main_manager; Users users;
	std::cout << "\nBroj ucitanih racuna je " << main_manager.invoice_array.size() << "\n";
	for (int i = 0; i < main_manager.invoice_array.size(); ++i) {
		std::cout << main_manager.invoice_array[i];
		std::cout<< std::endl << "================\n";
	}
	std::cout << "ERORI\n";
	for (int i = 0; i < main_manager.invoice_array_invalid.size(); ++i) {
		std::cout << main_manager.invoice_array_invalid[i];
		std::cout << std::endl << "================\n";
		std::cout << main_manager.invoice_array.size();
		std::cout << main_manager.invoice_array_invalid.size();
	}

	
	Menu::UserUI(main_manager, &users);
	FileManager::saveToFolder("Users", "users.txt", (users.getJSON()).dump());
}