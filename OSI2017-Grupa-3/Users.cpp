#include "Users.h"
#include <algorithm>
#include <vector>
#include "InvoiceManager.h"

Users::Users() : count(0), capacity(10)
{
	string s = InvoiceManager::getStringFromFile("users.txt");
	std::cout << s;

	users = new User[capacity];
	if (s.empty()) {
		addUser("admin", "1234");
	}
	else {
		try {
			loadFromJSON(nlohmann::json::parse(s));
		}
		catch (std::exception &e) {
			addUser("admin", "1234");
		}
	}

}

Users::~Users()
{
	delete[] users;
}

std::string Users::addUser(std::string name, std::string surname, std::string pin)
{
	std::string username = "";
	std::cout << "Unesite korisnicko ime: ";
	std::cin >> username;
	if (!userAlreadyExists(username, pin)) {
		int userType;
		std::cout << "Unos administratora [1]" << std::endl << "Unos analiticara [0]" << std::endl;
		do {
			std::cin >> userType;
		} while (userType != 0 && userType != 1);
		User temp(name, surname, username, pin, userType);
		capacityCheck();
		users[count++] = temp;
		return "1";
	}
	return "0Korisnik vec postoji.";
}

std::string Users::addUser(std::string username, std::string pin)
{
	users[count++] = User("", "", username, pin, 1);
	return "1";
}

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

void Users::capacityCheck()
{
	if (count == capacity) {
		User* temp = users;
		users = new User[capacity *= 2];
		for (int i = 0; i < count; i++)
			users[i] = temp[i];
	}
}

bool Users::userAlreadyExists(std::string username, std::string pin)
{
	for (int i = 0; i < count; i++)
		if (users[i].username == username&&users[i].getPin() == pin)
			return true;
	return false;
}

bool Users::userAlreadyExists(std::string username)
{
	for (int i = 0; i < count; i++)
		if (users[i].username == username)
			return true;
	return false;
}

json Users::getJSON() {
	json j = json{ 
		{ "count", count },
		{ "capacity", capacity },
	};
	std::vector<std::string> v;
	for (int i = 0; i < count; ++i)
		v.push_back(users[i].getEncryptedJSON());
	j["users"] = v;
	return j;
}

void Users::loadFromJSON(json j) {
	count = j.at("count").get<int>();
	capacity= j.at("capacity").get<int>();
	std::vector<std::string> v = j.at("users").get<std::vector<std::string>>();
	for (int i = 0; i < count; i++)
		users[i].loadFromEncryptedJSON(v[i]);
}