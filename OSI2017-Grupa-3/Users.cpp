#include "Users.h"
#include <algorithm>
#include <vector>
#include "InvoiceManager.h"

Users::Users()
{
	string exe = FileManager::getexepath();
	string s = FileManager::getStringFromFile((exe + "Users\\users.txt").c_str());
	
	//Pokusaj ucitavanja korisnika iz fajla "users.txt"
	try {
		std::string test = s;
		test.pop_back();
		if (test.empty())
			throw("Datoteka sa podacima o korisnicima je prazna.");
		loadFromJSON(nlohmann::json::parse(s));
	}
	catch (const char* message) {
		std::cout << message << std::endl;
		addUser();	//Dodavanje korisnika "admin" ukoliko je fajl prazan
	}
}

/*Metoda koja dodaje novog korisnika u sistem*/
std::string Users::addUser(std::string name, std::string surname)
{
	std::string username = "";
	int userType;
	std::cout <<std::endl<< " =====================================================================================" << std::endl;
	std::cout << "|                           UNESITE REDNI BROJ OPCIJE:                                |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << "|[0] Unos analiticara                                                                 |" << std::endl;
	std::cout << "|[1] Unos administratora                                                              |" << std::endl;
	std::cout << "|                                                                                     |" << std::endl;
	std::cout << " =====================================================================================" << std::endl;
	do {
		while (!(std::cin >> userType)) {		//Onemogucavanje unosa pogresnog tipa
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (userType != 0 && userType != 1)
			std::cout << "Neispravan unos, pokusajte ponovo." << std::endl;
	} while (userType != 0 && userType != 1);
	system("CLS");
	std::cout << "Unesite korisnicko ime: ";
	std::cin >> username;
	if (!userAlreadyExists(username)) {
		int ctrl;
		User temp;
		do {
			ctrl = 0;
			std::string pin = "";
			std::cout << "Unesite pin kod: ";
			std::cin >> pin;
			temp = User(name, surname, username, pin, userType);
			if (temp.hasErrors()[0] == '0') {
				std::string message = temp.hasErrors();
				std::cout << message.erase(0, 1);
				ctrl = 1;
			}
		} while (ctrl);
		users.push_back(temp);
		return "1";
	}
	return "0Korisnik vec postoji.";
}

/*Metoda koja dodaje korisnika sa korisnickim imenom "admin".
Poziva se samo ukoliko je fajl iz koga se ucitavaju korisnici prazan.*/
std::string Users::addUser()
{
	users.push_back(User("", "", "admin", "1234", 1));
	return "1";
}

/*Metoda koja provjerava da li su podaci za prijavljivanje na sistem ispravni i vraca poruku o tipu greske ukoliko nisu*/
std::string Users::loginUser(std::string username, std::string pin, User& user)
{
	if (!userAlreadyExists(username))
		return "0Korisnik ne postoji.";
	if (!userAlreadyExists(username, pin))
		return "0Netacan pin.";
	for (int i = 0; i < users.size(); i++)
		if (users[i].username == username) {
			user = users[i];
			break;
		}
	return "1";
}

/*Metoda koja sluzi za brisanje korisnika iz sistema*/
std::string Users::deleteUser(std::string username)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i].username == username) {
			users.erase(users.begin() + i);
			return "1";
		}
	return "0Korisnik nije pronadjen.";
}

/*Metoda koja vraca informaciju da li postoji korisnik sa datim korisnickim imenom i pin kodom*/
bool Users::userAlreadyExists(std::string username, std::string pin)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i].username == username&&users[i].getPin() == pin)
			return true;
	return false;
}

/*Metoda koja vraca informaciju da li postoji korisnik sa datim korisnickim imenom*/
bool Users::userAlreadyExists(std::string username)
{
	for (int i = 0; i < users.size(); i++)
		if (users[i].username == username)
			return true;
	return false;
}

/*Metoda koja formira JSON objekat od objekta klase Users*/
json Users::getJSON()
{
	std::vector<std::string> v;
	for (int i = 0; i < users.size(); ++i)
		v.push_back(users[i].getEncryptedJSON());	//Formiranje enkriptovanog niza stringova koji predstavljaju podatke o korisnicima
	json j = json{
		{ "users", v }
	};
	return j;
}

/*Metoda koja formira objekat klase Users na osnovu podataka odgovarajuceg JSON objekta*/
void Users::loadFromJSON(json j) 
{
	std::vector<std::string> v = j.at("users").get<std::vector<std::string>>();
	for (int i = 0; i < v.size(); i++) {
		User temp;
		temp.loadFromEncryptedJSON(v[i]);		//Ucitavanje korisnika iz JSON objekta i njihova dekripcija
		users.push_back(temp);
	}
}

Users::~Users()
{}