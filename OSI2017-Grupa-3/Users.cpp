#include "Users.h"
#include <algorithm>
#include <vector>
#include "InvoiceManager.h"

Users::Users() : count(0), capacity(10)
{
	string s = InvoiceManager::getStringFromFile("users.txt");

	users = new User[capacity];
	
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

Users::~Users()
{
	delete[] users;
}

/*Metoda koja dodaje novog korisnika u sistem*/
std::string Users::addUser(std::string name, std::string surname)
{
	std::string username = "";
	std::cout << "Unesite korisnicko ime: ";
	std::cin >> username;
	if (!userAlreadyExists(username)) {
		int userType, ctrl;
		std::cout << "Unos administratora [1]" << std::endl << "Unos analiticara [0]" << std::endl;
		do {
			std::cin >> userType;
		} while (userType != 0 && userType != 1);
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
		capacityCheck();
		users[count++] = temp;
		return "1";
	}
	return "0Korisnik vec postoji.";
}

/*Metoda koja dodaje korisnika sa korisnickim imenom "admin".
Poziva se samo ukoliko je fajl iz koga se ucitavaju korisnici prazan.*/
std::string Users::addUser()
{
	users[count++] = User("", "", "admin", "1234", 1);
	return "1";
}

/*Metoda koja provjerava da li su podaci za prijavljivanje na sistem ispravni i vraca poruku o tipu greske ukoliko nisu*/
std::string Users::loginUser(std::string username, std::string pin, User& user)
{
	if (!userAlreadyExists(username))
		return "0Korisnik ne postoji.";
	if (!userAlreadyExists(username, pin))
		return "0Netacan pin.";
	for(int i=0;i<count;i++)
		if (users[i].username == username) {
			user = users[i];
			break;
		}
	return "1";
}

/*Metoda koja sluzi za brisanje korisnika iz sistema*/
std::string Users::deleteUser(std::string username)
{
	for (int i = 0; i < count; i++)
		if (users[i].username == username) {
			for (int j = i; j < count; j++)
				users[j] = users[j + 1];
			--count;
			return "1";
		}
	return "0Korisnik nije pronadjen.";
}

/*Metoda koja provjerava da li ima dovoljno alociranog prostora za niz korisnika i povecava kapacitet ukoliko nema*/
void Users::capacityCheck()
{
	if (count == capacity) {
		User* temp = users;
		users = new User[capacity *= 2];
		for (int i = 0; i < count; i++)
			users[i] = temp[i];
	}
}

/*Metoda koja vraca informaciju da li postoji korisnik sa datim korisnickim imenom i pin kodom*/
bool Users::userAlreadyExists(std::string username, std::string pin)
{
	for (int i = 0; i < count; i++)
		if (users[i].username == username&&users[i].getPin() == pin)
			return true;
	return false;
}

/*Metoda koja vraca informaciju da li postoji korisnik sa datim korisnickim imenom*/
bool Users::userAlreadyExists(std::string username)
{
	for (int i = 0; i < count; i++)
		if (users[i].username == username)
			return true;
	return false;
}

/*Metoda koja formira JSON objekat od objekta klase Users*/
json Users::getJSON()
{
	std::vector<std::string> v;
	for (int i = 0; i < count; ++i)
		v.push_back(users[i].getEncryptedJSON());	//Formiranje enkriptovanog niza stringova koji predstavljaju podatke o korisnicima
	json j = json{
		{ "count", count },
		{ "capacity", capacity },
		{ "users", v }
	};
	return j;
}

/*Metoda koja formira objekat klase Users na osnovu podataka odgovarajuceg JSON objekta*/
void Users::loadFromJSON(json j) 
{
	count = j.at("count").get<int>();
	capacity= j.at("capacity").get<int>();
	std::vector<std::string> v = j.at("users").get<std::vector<std::string>>();
	for (int i = 0; i < count; i++)
		users[i].loadFromEncryptedJSON(v[i]);	//Ucitavanje korisnika iz JSON objekta i njihova dekripcija
}