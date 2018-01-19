#pragma once
#include <string>
#include <iostream>
using std::string;

class Message
{
	static void deductFirst(string&); //funkcija koja brise prvi znak string-a
	static bool isGoodFormat(string); //funkcija za provjeru formata poruke
public:
	static bool isSuccess(string); //funkcija za provjeru da li je poruka o uspjehu ili neuspjehu
	static string getMessage(string); //funkcija koja provjerava uspjeh poruke i vrsi njeno formatiranje u konacni oblik
};

