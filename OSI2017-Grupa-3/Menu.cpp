#include "Menu.h"
#include "InvoiceManager.h"

bool Menu::requestLogin(Users& users, User &user)
{
	std::string pin, name, result;
	std::cout << "Unesite korisnicko ime:";
	std::cin >> name;
	std::cout << std::endl << "Unesite sifru:";
	std::cin >> pin;

	result = users.loginUser(name, pin, user);

	if (Message::isSuccess(result))
	{
		std::cout << "Uspjesna prijava korisnika " << name <<"."<< std::endl;
		return true;
	}
	else std::cout << Message::getMessage(result);
	return false;
}

void Menu::adminOptions(Users &users)
{
	int i;
	std::cout << "=====================================================================================" << std::endl;
    std::cout << "Unesite 1 za opciju upravljanja korisnickim nalozima." << std::endl;
	std::cout << "Unesite 2 za opciju podesavanja valute." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za administratora." << std::endl;
	std::cout << "=====================================================================================" << std::endl;
	std::cin >> i;
	if (i == 1)
	  adminUserControl(users);//rad sa korisnickim nalozima
	else if (i == 2);
	//rad sa valutom - trenutno nezavrsen dio
	std::cout << std::endl << "Zavrsili ste sa koristenjem administratorovih opcija.";
}

void Menu::analystOptions(Invoice *invoices)
{
	int i;
	std::cout << "==================================================================================" << std::endl;
	std::cout << "Unesite 1 za opciju pregleda racuna za odredjenog kupca." << std::endl;
	std::cout << "Unesite 2 za opciju pregleda racuna za odredjeni mjesec." << std::endl;
	std::cout << "Unesite 3 za opciju pregleda racuna za odredjeni proizvod." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za analiticara." << std::endl;
	std::cout << "==================================================================================" << std::endl;
	std::cin >> i;
	if (i == 1)
	{
		std::string buyer;
		std::cout << "Unesite ime kupca:";
		std::cin >> buyer;
		std::vector<Invoice> buyers = InvoiceFilter::filter_by_buyer(invoices, InvoiceManager::Instance->invoice_array.size() , buyer);
		std::cout << std::endl << "Racuni za odredjenog kupca:"<<std::endl;
		for (Invoice x : buyers)
			x.print();
	}
	else if (i == 2)
	{
		std::string date;
		do {
			std::cout << "Unesite datum:";
			std::cin >> date;
		} while (!Invoice::properDateFormat(date));
		std::vector<Invoice> dates = InvoiceFilter::filter_by_date(invoices, InvoiceManager::Instance->invoice_array.size(), date);
		std::cout << std::endl << "Racuni za odredjeni datum:" << std::endl;
		for (Invoice x : dates)
			x.print();
	}
	else if (i == 3)
	{
		std::string art_name;
		std::cout << "Unesite proizvod:";
		std::cin >> art_name;
		std::vector<Invoice> names = InvoiceFilter::filter_by_name(invoices, InvoiceManager::Instance->invoice_array.size(), art_name);
		std::cout << std::endl << "Racuni za odredjeni proizvod:" << std::endl;
		for (Invoice x : names)
			x.print();
	}
	std::cout << std::endl << "Zavrsili ste sa koristenjem analiticarovih opcija.";
}


void Menu::adminUserControl(Users &users)
{
	int i;
	std::cout << "==================================================================================" << std::endl;
	std::cout << "Unesite 1 za opciju dodavanja korisnika." << std::endl;
	std::cout << "Unesite 2 za opciju brisanja korisnika." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za upravljanje korisnickim nalozima." << std::endl;
	std::cout << "==================================================================================" << std::endl;
	std::cin >> i;
	if (i == 1)
	{
		std::string name, surname, pin,message;
		std::cout << std::endl << "Unesite ime:";
		std::cin >> name;
		std::cout << std::endl << "Unesite prezime:";
		std::cin >> surname;
		std::cout << std::endl << "Unesite pin:";
		std::cin >> pin;
		message=users.addUser(name, surname, pin);
		if (message[0] == '1') std::cout << std::endl << "Uspjesno ste dodali novog korisnika.";
		else std::cout << std::endl << Message::getMessage(message);
	}
	else if (i == 2)
	{
		std::string username,message;
		std::cout << std::endl << "Unesite korisnicko ime korisnika kojeg zelite da obrisete:";
		std::cin >> username;
		message=users.deleteUser(username);
		if (message[0] == '1') std::cout << std::endl << "Uspjesno ste obrisali korisnika " << username << ".";
		else std::cout << std::endl << Message::getMessage(message);
	}
	std::cout << std::endl << "Zavrsili ste sa koristenjem opcija za upravljanje korisnickim nalozima.";
}