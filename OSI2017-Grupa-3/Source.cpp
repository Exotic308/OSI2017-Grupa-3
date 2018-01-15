﻿//потребно за унос или приказ података
#include <iostream>
#include "Message.h"
#include "InvoiceParser.h"
#include "Invoice.h"
#include "Users.h"
#include "InvoiceManager.h"
#include"Menu.h"

//Почетни портал
void main() {
	std::cout << "Pocetni portal projektnog zadatka OSI2017-Grupa-3" << std::endl;

	//Тестирање уноса рачуна
	InvoiceManager main_manager;
	std::cout << "\nBroj ucitanih racuna je " << main_manager.invoice_array.size()<<"\n";
	for (int i = 0; i < main_manager.invoice_array.size(); ++i) {
		main_manager.invoice_array[i].print();
	}
	//Тестирање чувања енкриптоване Users инстанце у текстуалну датотеку
	Users* users = new Users();
	/*users->addUser("neven", "ignjic", "1234");
	users->addUser("marko", "krstovic", "5678");
	json j = users->getJSON();
	std::string s = j.dump();
	std::cout << s;
	users->loadFromJSON(j);
	User& u = (*new User());
	std::cout << "\n"<<users->loginUser("neco", "12345", u);*/

	User user; bool control = false;
	do
	{
		control = Menu::requestLogin(*users, user);//ISPRAVITI users AKO SE PROMJENI NACIN INSTANCIRANJA
		if (!control) std::cout << std::endl << "Pokusajte ponovo." << std::endl;
	} while (!control);

	control = false;
	Invoice *invoices = Invoice::castFromVectorToPointer(main_manager.invoice_array);
	do
	{
		int x;
		if (user.isAdmin()) Menu::adminOptions(*users);//ISPRAVITI users AKO SE PROMJENI NACIN INSTANCIRANJA
		else
			Menu::analystOptions(invoices);

		std::cout << std::endl << "Unesite 1 za novo pokretanje programa ili bilo koji karakter za kraj rada..."<<std::endl;
		std::cin >> x;
		if (x == 1) control = false;
		else control = true;
	} while (!control);
	//ОВО ТРЕБА ЕНКАПСУЛИРАТ
	//try {
		FileManager::saveToFile("users.txt", (users->getJSON()).dump());
	//}
	//catch (std::exception &e) {}
	getchar();
	getchar();
}