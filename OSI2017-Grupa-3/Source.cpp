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
	InvoiceManager main_manager; Users users;/*
	std::cout << "\nBroj ucitanih racuna je " << main_manager.invoice_array.size() << "\n";
	for (int i = 0; i < main_manager.invoice_array.size(); ++i) {
		main_manager.invoice_array[i].print();
	}
	std::cout << "\n\n\nFILTER RADI\n\n\n";
	std::vector<Invoice> filtered2 = InvoiceFilter::filter_by_buyer(&main_manager.invoice_array[0], main_manager.invoice_array.size(), "ABC");
	std::vector<Invoice> filtered = InvoiceFilter::filter_by_date(&main_manager.invoice_array[0], main_manager.invoice_array.size(), "24/10/2017");
	std::vector<Invoice> filtered3 = InvoiceFilter::filter_by_name(&main_manager.invoice_array[0], main_manager.invoice_array.size(), "abc");
	for (int i = 0; i < filtered.size(); i++) filtered[i].print();
	std::cout << "=================================\n";
	for (int i = 0; i < filtered2.size(); i++) filtered2[i].print();
	std::cout << "=================================\n";
	for (int i = 0; i < filtered3.size(); i++) filtered3[i].print();
	std::cout << "=================================\n";*/

	users.addUser("Milos", "Trivundza");//тестни корисник
	Menu::UserUI(main_manager, &users);

	FileManager::saveToFile("users.txt", (users.getJSON()).dump());

	getchar();
	getchar();
}