#include "Message.h"

void Message::deductFirst(string& message)
{
	message.erase(0, 1);
}

bool Message::isGoodFormat(string message)
{
	return message[0] == '0' || message[0] == '1';
}

bool Message::isSuccess(string message)
{
	if (isGoodFormat(message))
	{
		if (message[0] == '1') return true;
	}
	else std::cout << "Neispravan oblik poruke." << std::endl;
	return false;
}

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