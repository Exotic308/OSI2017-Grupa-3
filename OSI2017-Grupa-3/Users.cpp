#include "Users.h"



Users::Users() : count(0), capacity(10)
{
	users = new User[capacity];
	std::ifstream file;
	std::string temp = "";
	file.open("Users.txt");
	while (!file.eof()) {
		capacityCheck();
		std::getline(file, temp);
		nlohmann::json j = nlohmann::json::parse(temp);
		users[count++] = j;
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
		std::string username = "";
		std::cout << "Unesite korisnicko ime: ";
		getline(std::cin, username);
		User temp(name, surname, username, pin, userType);
		capacityCheck();
		users[count++] = temp;
		return "1";
	}
	return "0Korisnik vec postoji.";
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

void Users::saveUsers()
{
	nlohmann::json j;
	std::ofstream output;
	output.open("Users.txt");
	for (int i = 0; i < count; i++) {
		j = users[i];
		output << j << std::endl;
	}
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
