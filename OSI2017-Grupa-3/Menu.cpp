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
		{//MILOS LUKIC TO FIX THIS SO IT DOESNT HAVE BREAK
			if (main_manager.invoice_array.size() == 0)
			{
				std::cout << "Nemoguce koristiti opcije za analiticara jer nije ucitan nijedan racun.";
				break;//PLS NO BREAK VATAFAK
			}
			Menu::analystOptions(&main_manager.invoice_array[0]);
		}

		std::cout << std::endl << "Unesite 1 za novo pokretanje programa ili bilo koji karakter za kraj rada..." << std::endl;
		std::cin >> option;
		if (option == 1) control = false;
		else control = true;
	} while (!control);
}

//Metoda za prijavu korisnika
bool Menu::requestLogin(Users& users, User &user)
{
	std::cout << std::endl << "PRIJAVA:" << std::endl;
	std::string pin, name, result;
	std::cout << "Unesite korisnicko ime:";
	std::cin >> name;
	std::cout << std::endl << "Unesite sifru:";
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
	std::cout << "=====================================================================================" << std::endl;
    std::cout << "Unesite 1 za opciju upravljanja korisnickim nalozima." << std::endl;
	std::cout << "Unesite 2 za opciju podesavanja valute." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za administratora." << std::endl;
	std::cout << "=====================================================================================" << std::endl;
	std::cin >> options;
	if (options == 1)
	  adminUserControl(users);//rad sa korisnickim nalozima(poziv druge metode)
	else if (options == 2);
	//rad sa valutom - trenutno nezavrsen dio
	std::cout << std::endl << "Zavrsili ste sa koristenjem administratorovih opcija."<<std::endl;
}

//Metoda koja nudi opcije za analiticara.
void Menu::analystOptions(Invoice *invoices)
{
	int options;
	std::cout << "==================================================================================" << std::endl;
	std::cout << "Unesite 1 za opciju pregleda racuna za odredjenog kupca." << std::endl;
	std::cout << "Unesite 2 za opciju pregleda racuna za odredjeni mjesec." << std::endl;
	std::cout << "Unesite 3 za opciju pregleda racuna za odredjeni proizvod." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za analiticara." << std::endl;
	std::cout << "==================================================================================" << std::endl;
	std::cin >> options;
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
	std::cout << "==================================================================================" << std::endl;
	std::cout << "Unesite 1 za opciju dodavanja korisnika." << std::endl;
	std::cout << "Unesite 2 za opciju brisanja korisnika." << std::endl;
	std::cout << "Unesite bilo koji karakter za izlaz iz opcija za upravljanje korisnickim nalozima." << std::endl;
	std::cout << "==================================================================================" << std::endl;
	std::cin >> options;
	if (options == 1)//dodavanje novog korisnika
	{
		std::string name, surname, pin,message;
		std::cout << std::endl << "Unesite ime:";
		std::cin >> name;
		std::cout << std::endl << "Unesite prezime:";
		std::cin >> surname;
		message=users.addUser(name, surname); 
		if (message[0] == '1') std::cout << std::endl << "Uspjesno ste dodali novog korisnika.";
		else std::cout << std::endl << Message::getMessage(message);
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