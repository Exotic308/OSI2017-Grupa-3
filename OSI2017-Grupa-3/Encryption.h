#pragma once
#include <iostream>
#include <ctime>
#include <string>

class Encryption
{
	int key;
public:
	Encryption();

	std::string encryptedMessage = "";
	inline int getKey() { return key; }

	void encrypt(std::string);
	std::string decrypt();
	std::string decrypt(int);
private:
	void generateKey();
};