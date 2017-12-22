//потребно за унос или приказ података
#include <iostream>
#include "Message.h"
#include "InvoiceParser.h"
#include "Invoice.h"
#include "Users.h"

//Почетни портал
void main() {
	std::cout << "Pocetni portal projektnog zadatka OSI2017-Grupa-3" << std::endl;

	//Тестирање уноса рачуна
	InvoiceParser* ips = new InvoiceParser();
	Invoice invoice = *(new Invoice());
	std::cout << InvoiceParser::racun1;
	string message = ips->parseFromText(invoice, InvoiceParser::racun1);
	std::cout << std::endl;
	if (!Message::isSuccess(message))
		std::cout << message;
	invoice.print();

	//Тестирање чувања енкриптоване Users инстанце у текстуалну датотеку
	/*Users* users = new Users();
	users->addUser("neven", "ignjic", "1234");
	users->addUser("marko", "krstovic", "5678");
	json j = users->getJSON();
	std::string s = j.dump();
	std::cout << s;
	users->loadFromJSON(j);
	User& u = (*new User());
	std::cout << "\n"<<users->loginUser("neco", "12345", u);*/

	getchar();
	getchar();
}