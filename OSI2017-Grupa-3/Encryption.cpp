#include "Encryption.h"



/*Metoda koja vrsi enkripciju stringa ukoliko nije enkriptovan, odnosno dekripciju ukoliko jeste*/
std::string Encryption::xorEncryptDecrypt(std::string s) {
	char key[3] = { 'K', 'C', 'Q' };
	std::string output = s;
	for (int i = 0; i < s.size(); i++)
		output[i] = s[i] ^ key[i % (sizeof(key) / sizeof(char))];
	return output;
}