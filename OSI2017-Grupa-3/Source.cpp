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
		main_manager.invoice_array[i].print();
		std::cout<< std::endl << "================\n";
	}
	std::cout << "ERORI\n";
	for (int i = 0; i < main_manager.invoice_array_invalid.size(); ++i) {
		main_manager.invoice_array_invalid[i].print();
		std::cout << std::endl << "================\n";
		std::cout << main_manager.invoice_array.size();
		std::cout << main_manager.invoice_array_invalid.size();
	}
	

	users.addUser("Milos", "Trivundza");//тестни корисник
	Menu::UserUI(main_manager, &users);

	

	FileManager::saveToFile(path+"users.txt", (users.getJSON()).dump());

	getchar();
	getchar();
}