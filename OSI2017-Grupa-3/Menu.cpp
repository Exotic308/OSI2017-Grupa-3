#include "Menu.h"

bool Menu::requestLogin(User &user)
{
	std::string pin, name, result;
	std::cout << "Unesite korisnicko ime:";
	std::cin >> name;
	std::cout << std::endl << "Unesite sifru:";
	std::cin >> pin;

	result = loginUser(name, pin,user);

	if (Message::isSuccess(result))
	{
		std::cout << "Uspjesna prijava korisnika " << name << std::endl;
		return true;
	}
	else std::cout << Message::getMessage(result);
	return false;
}

void Menu::adminOptions()
{
	int i;
	std::cout << "================================================================" << std::endl;
    std::cout << "Unesite 1 za opciju upravljanja korisnickim nalozima." << std::endl;
	std::cout << "Unesite 2 za opciju podesavanja valute." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za administratora." << std::endl;
	std::cout << "================================================================" << std::endl;
	std::cin >> i;
	if (i == 1);
	//rad sa korisnickim nalozima - trenutno nezavrsen dio
	else if (i == 2);
	//rad sa valutom - trenutno nezavrsen dio
	else
		std::cout << std::endl << "Zavrsili ste sa koristenjem administratorovih opcija.";
}

void Menu::analystOptions(Invoice *invoices)
{
	int i;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Unesite 1 za opciju pregleda racuna za odredjenog kupca." << std::endl;
	std::cout << "Unesite 2 za opciju pregleda racuna za odredjeni mjesec." << std::endl;
	std::cout << "Unesite 3 za opciju pregleda racuna za odredjeni proizvod." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za analiticara." << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cin >> i;
	if (i == 1);
	  //filter_by_buyer(...); std::cout<< vector koji vraca ovaj filter
	else if (i == 2);
	  //filter_by_date(...); std::cout<< vector koji vraca ovaj filter
	else if (i == 3);
	  //filter_by_name(...); std::cout<< vector koji vraca ovaj filter
	else 
		std::cout << std::endl << "Zavrsili ste sa koristenjem analiticarovih opcija.";
}
