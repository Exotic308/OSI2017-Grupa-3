#include "Menu.h"
#include "InvoiceManager.h"

//Metoda koja predstavlja korisnicki interfejs.
void Menu::UserUI(InvoiceManager &main_manager, Users *users)
{
	User user; bool control = false;//kontrola izlaza iz petlji
	do
	{
		control = Menu::requestLogin(*users, user);
		if (!control) 
			std::cout << std::endl << "Pokusajte ponovo." << std::endl;

	} while (!control);

	control = false;
	do
	{
		int option;
		if (user.isAdmin()) Menu::adminOptions(*users);
		else
		{
			main_manager.scanForNewInvoices();
			if (main_manager.invoice_array.size() == 0)
				std::cout << "Nije moguce koristiti opcije za analiticara jer nije ucitan nijedan racun.";
			else
				Menu::analystOptions(&main_manager.invoice_array[0]);
		}

		std::cout << std::endl << "Izaberite opciju:" << std::endl;
		std::cout << "[1] Povratak na opcije." << std::endl;
		std::cout << "[2] Izlazak iz programa." << std::endl;
		while (!(std::cin >> option)) {		//Onemogucavanje unosa pogresnog tipa, isti blok se koristi i u daljem kodu
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (option == 1) control = false;
		else control = true;
	} while (!control);
}

//Metoda za prijavu korisnika
bool Menu::requestLogin(Users& users, User &user)
{
	std::cout << " =====================================================================================" << std::endl;
	std::cout << "|                                     PRIJAVA                                         |" << std::endl;
	std::cout << " =====================================================================================" << std::endl;
	std::string pin, name, result;
	std::cout << "Unesite korisnicko ime:";
	std::cin >> name;
	std::cout << std::endl << "Unesite PIN:";
	std::cin >> pin;

	result = users.loginUser(name, pin, user);//prijava korisnika(vraca odgovarajucu poruku)

	if (Message::isSuccess(result))
	{
		std::cout << "Uspjesna prijava korisnika " << name <<"."<< std::endl;
		return true;
	}
	else std::cout << Message::getMessage(result);
	return false;
}

//Metoda koja nudi opcije za administratora
void Menu::adminOptions(Users &users)
{
	int options;
	std::cout << " =====================================================================================" << std::endl;
    std::cout << "|                           UNESITE REDNI BROJ OPCIJE:                                |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[1] Upravljanje korisnickim nalozima                                                 |" << std::endl;
	std::cout << "|[2] Podesavanje valute.                                                              |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[0] Izlaz iz administratorskih opcija.                                               |" << std::endl;
	std::cout << " =====================================================================================" << std::endl;
	do {
		while (!(std::cin >> options)) {
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (options != 1 && options != 2 && options != 0)
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
	} while (options != 1 && options != 2 && options != 0);
	system("CLS");
	if (options == 1)
	  adminUserControl(users);//rad sa korisnickim nalozima(poziv druge metode)
	else if (options == 2)
	{
		std::cout << "Unesite novi koeficijent valute u odnosu na konvertibilnu marku (BAM):" << std::endl;
		do {
			while (!(std::cin >> InvoiceItem::currencyCoefficient)) {
				std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (InvoiceItem::currencyCoefficient < 0)
				std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
		} while (InvoiceItem::currencyCoefficient < 0);
		FileManager::saveToFolder("Valuta", "valuta.txt", std::to_string(InvoiceItem::currencyCoefficient));
	}
	std::cout << std::endl << "Zavrsili ste sa koristenjem administratorovih opcija."<<std::endl;
}

//Metoda koja nudi opcije za analiticara.
void Menu::analystOptions(Invoice *invoices)
{
	int options;
	std::cout << " =====================================================================================" << std::endl;
	std::cout << "|                           UNESITE REDNI BROJ OPCIJE:                                |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[1] Pregled racuna za odredjenog kupca                                               |" << std::endl;
	std::cout << "|[2] Pregled racuna za odredjeni mjesec                                               |" << std::endl;
	std::cout << "|[3] Pregled racuna za odredjeni proizvod                                             |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[0] Izlaz iz opcija analiticara                                                      |" << std::endl;
	std::cout << " =====================================================================================" << std::endl;
	do {
		while (!(std::cin >> options)) {
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (options != 1 && options != 2 && options != 3 && options != 0)
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
	} while (options != 1 && options != 2 && options != 3 && options != 0);
	system("CLS");
	if (options == 1)
	{
		std::string buyer;
		std::cout << "Unesite ime kupca:";
		std::cin >> buyer; //ime koje se salje kao argument u metodu filter
		std::vector<Invoice> buyers = InvoiceFilter::filter_by_buyer(invoices, (int)InvoiceManager::Instance->invoice_array.size() , buyer);
		std::cout << std::endl << "Racuni za odredjenog kupca:"<<std::endl;
		for (Invoice x : buyers)//ispis
			std::cout << x << std::endl;
	}
	else if (options == 2)
	{
		std::string date;
		do {
			std::cout << "Unesite datum:";
			std::cin >> date; //datum koji se salje kao argument u metodu filter
		} while (!Invoice::properDateFormat(date));
		std::vector<Invoice> dates = InvoiceFilter::filter_by_date(invoices, (int)InvoiceManager::Instance->invoice_array.size(), date);
		std::cout << std::endl << "Racuni za odredjeni datum:" << std::endl;
		for (Invoice x : dates)//ispis
			std::cout << x << std::endl;
	}
	else if (options == 3)
	{
		std::string art_name;
		std::cout << "Unesite proizvod:";
		std::cin >> art_name; //ime koje se salje kao argument u metodu filter
		std::vector<Invoice> names = InvoiceFilter::filter_by_name(invoices, (int)InvoiceManager::Instance->invoice_array.size(), art_name);
		std::cout << std::endl << "Racuni za odredjeni proizvod:" << std::endl;
		for (Invoice x : names)//ispis
			std::cout << x << std::endl;
	}
	std::cout << std::endl << "Zavrsili ste sa koristenjem analiticarovih opcija."<<std::endl;
}

//Metoda za kontrolu korisnickim nalozima.
void Menu::adminUserControl(Users &users)
{
	int options;
	std::cout << " =====================================================================================" << std::endl;
	std::cout << "|                           UNESITE REDNI BROJ OPCIJE:                                |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[1] Dodavanje korisnika                                                              |" << std::endl;
	std::cout << "|[2] Brisanje korisnika                                                               |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[0] Izlaz iz administratorskih opcija.                                               |" << std::endl;
	std::cout << " =====================================================================================" << std::endl;
	do {
		while (!(std::cin >> options)) {
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (options != 1 && options != 2 && options != 0)
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
	} while (options != 1 && options != 2 && options != 0);
	system("CLS");
	if (options == 1)//dodavanje novog korisnika
	{
		std::string name, surname, pin,message;
		std::cout << std::endl << "Unesite ime:";
		std::cin >> name;
		std::cout << "Unesite prezime:";
		std::cin >> surname;
		message=users.addUser(name, surname); 
		if (Message::isSuccess(message)) 
			std::cout << std::endl << "Uspjesno ste dodali novog korisnika.";
		else 
			std::cout << std::endl << Message::getMessage(message);
	}
	else if (options == 2)//brisanje korisnika
	{
		std::string username,message;

		std::cout << std::endl << "Unesite korisnicko ime korisnika kojeg zelite da obrisete:";
		std::cin >> username;

		message=users.deleteUser(username);

		if (message[0] == '1') 
			std::cout << std::endl << "Uspjesno ste obrisali korisnika " << username << '.';
		else 
			std::cout << std::endl << Message::getMessage(message);
	}
	std::cout << std::endl << "Zavrsili ste sa koristenjem opcija za upravljanje korisnickim nalozima."<<std::endl;
}