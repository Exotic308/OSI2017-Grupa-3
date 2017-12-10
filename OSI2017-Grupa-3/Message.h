#pragma once
#include <string>
#include <iostream>
using std::string;

class Message
{
	static void deductFirst(string&);
	static bool isGoodFormat(string);
public:
	static bool isSuccess(string);
	static string getMessage(string);
};

