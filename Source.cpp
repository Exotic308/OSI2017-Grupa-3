#include "Message.h"
using std::string;

int main()
{
	string test1 = "1goodmessage";
	string test2 = "0goodform";
	string test3 = "wrongform";
	string test11 = Message::getMessage(test1);
	string test12 = Message::getMessage(test2);
	string test13 = Message::getMessage(test3);  //stampa error
	bool test_bool1 = Message::isSuccess(test1);
	bool test_bool2 = Message::isSuccess(test2);
	bool test_bool3 = Message::isSuccess(test3); //stampa error
	std::cout << test_bool1 << " " << test11 << std::endl;
	std::cout << test_bool2 << " " << test12 << std::endl;
	std::cout << test_bool3 << " " << test13 << std::endl;
	getchar();
}