#pragma once
#include "Invoice.h"


class InvoiceParser
{
public:
	
	string parseFromText(Invoice &, string, string);
	static const string racun1;
	static const string racun2;
	static const string racun3;
	static const string racun4;
	static const string racun5;
private:
	string detectFormat(string);

	string parseFormat1(Invoice&, string);
	string parseFormat2(Invoice&, string);
	string parseFormat3(Invoice&, string);
	string parseFormat4(Invoice&, string);
	string parseFormat5(Invoice&, string,string);

	int moveRows(int, int, string);
	string getLineOfText(int&, string);
	void RemoveChar(string& str, char c);
	string getStringUntilComma(int&, string);
	int getNumberOfItemsFormat5(string);
	string turnToGoodFormat(string);
	string getStringOfNumbersUntilLetter(int&, string);

	void FormatParserNo5(std::string&); //izbacuje "Kupac"
};

