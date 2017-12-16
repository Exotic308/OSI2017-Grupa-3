//потребно за унос или приказ података
#include <iostream>
//Почетак
//Потребно за исписивање ћирилице у конзолу
#include <fcntl.h>
#include <io.h>
//крај

#include "Message.h"
//Почетни портал
void main() {
	//Постављање исписног мода на ћирилични
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << L"Почетни портал пројектног задатка OSI2017-Grupa-3" << std::endl;
	getchar();
}