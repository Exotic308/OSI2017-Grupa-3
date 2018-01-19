#include "Message.h"

/*Funkcija koja brise prvi znak string-a.*/
void Message::deductFirst(string& message)
{
	message.erase(0, 1);
}

/*Funkcija za provjeru formata poruke.*/
bool Message::isGoodFormat(string message)
{
	return message[0] == '0' || message[0] == '1';
}

/*Funkcija za provjeru da li je poruka o uspjehu ili neuspjehu i provjeri formata.*/
bool Message::isSuccess(string message)
{
	if (isGoodFormat(message))
	{
		if (message[0] == '1') return true;
	}
	else std::cout << "Neispravan oblik poruke." << std::endl;
	return false;
}

/*Funkcija koja provjerava uspjeh poruke i vrsi njeno formatiranje u konacni oblik.*/
string Message::getMessage(string message)
{
	if (isGoodFormat(message))
	{
		deductFirst(message);
		return message;
	}
	std::cout << "Neispravan oblik poruke." << std::endl;
	return message;
}