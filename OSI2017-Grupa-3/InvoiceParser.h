#pragma once
#include "Invoice.h"


class InvoiceParser
{
public:
	string parseFromText(Invoice &, string);
	static const string racun1;
private:
	int detectFormat(string);

	string parseFormat1(Invoice&, string);
	string parseFormat2(Invoice&, string);
	string parseFormat3(Invoice&, string);
	string parseFormat4(Invoice&, string);
	string parseFormat5(Invoice&, string);

	int moveRows(int, int,string);
	string getLineOfText(int&, string);
	void RemoveChar(string& str, char c);
};

