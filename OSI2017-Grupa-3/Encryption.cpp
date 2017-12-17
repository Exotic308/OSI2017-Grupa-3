#include "Encryption.h"



Encryption::Encryption()
{
	generateKey();
}

void Encryption::encrypt(std::string message)
{
	for (int i = 0; i < message.length(); i++)
		encryptedMessage += (message[i] + key);
}

std::string Encryption::decrypt()
{
	std::string result = "";
	for (int i = 0; i < encryptedMessage.length(); i++)
		result += (encryptedMessage[i] - key);
	return result;
}

std::string Encryption::decrypt(int key)
{
	std::string result = "";
	for (int i = 0; i < encryptedMessage.length(); i++)
		result += (encryptedMessage[i] - key);
	return result;
}

void Encryption::generateKey()
{
	srand(time(0));
	key = rand() % 100 + 1;
}
