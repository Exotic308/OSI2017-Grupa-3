//потребно за унос или приказ података
#include <iostream>
#include "Message.h"
#include "InvoiceParser.h"
#include "Invoice.h"

//Почетни портал
void main() {
	std::cout << "Pocetni portal projektnog zadatka OSI2017-Grupa-3" << std::endl;
	InvoiceParser* ips = new InvoiceParser();
	Invoice invoice = *(new Invoice());
	std::cout << InvoiceParser::racun1;
	string message = ips->parseFromText(invoice, InvoiceParser::racun1);
	std::cout << std::endl;
	if (!Message::isSuccess(message))
		std::cout << message;
	invoice.print();
	getchar();
}