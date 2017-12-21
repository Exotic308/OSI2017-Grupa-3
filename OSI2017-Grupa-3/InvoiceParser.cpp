#include "InvoiceParser.h"
#include <sstream>

using std::stringstream;

string InvoiceParser::parseFromText(Invoice &invoice, string invoiceText)
{
	int format = detectFormat(invoiceText);
	switch (detectFormat(invoiceText))
	{
	case 1: return parseFormat1(invoice, invoiceText);
	case 2: return parseFormat2(invoice, invoiceText);
	case 3: return parseFormat3(invoice, invoiceText);
	case 4: return parseFormat4(invoice, invoiceText);
	case 5: return parseFormat5(invoice, invoiceText);
	default: return "0Format racuna nije validan.";
	};
}

int InvoiceParser::detectFormat(string invoiceText)
{
	const int invalidFormat = 0;
	if (invoiceText[0] == 'K')/*Format 1 ili 4.*/
	{
		int newPosition = moveRows(3, 0, invoiceText);/*Pomjeramo se u red sa naslovom racuna.*/
		while (invoiceText[++newPosition] == ' ');
		if (invoiceText[newPosition] == 'R')/*Detektovan racun format 1.*/
			return 1;
		else if (invoiceText[newPosition] == 'O')
			return 4;/*Detektovan racun format 4.*/
		else return invalidFormat;
	}
	else if (invoiceText[0] == 'O')/*Format 2 ili 3.*/
	{
		int newPosition = moveRows(2, 0, invoiceText);
		if (invoiceText[newPosition] == '\n')
			return 2;/*Detektovan format 2.*/
		else
			return 3;/*Detektovan format 3.*/
	}
	else if (invoiceText[0] == 'S')
		return 5;/*Detektovan format 5.*/
	else
		return 0;/*Pogresan format.*/
}

string InvoiceParser::parseFormat1(Invoice &invoice, string invoiceText)
{
	int position = 0;
	char c;
	string stringValue;

	string line = getLineOfText(position, invoiceText);
	std::stringstream stringStream(line);
	stringStream >> stringValue >> invoice.buyer;/*Unosi ime kupca.*/

	line = getLineOfText(position, invoiceText);/*Unosi datum.*/
	stringstream stringStream1(line);
	stringStream1 >> stringValue >> invoice.date;

	line=getLineOfText(position, invoiceText);
	line=getLineOfText(position, invoiceText);
	line=getLineOfText(position, invoiceText);
	line=getLineOfText(position, invoiceText);/*Pomjeramo se na pocetak liste artikala.*/

	int savePosition = position, countItems = 0;
	while (line[0] != '-')
	{
		line = getLineOfText(position, invoiceText);
		countItems++;
	}
	--countItems;
	position = savePosition;
	invoice.items = new InvoiceItem[countItems];/*Cuvamo tu poziciju i brojimo koliko ima artikala.*/

	string value1, value2;
	for (int j = 0; j < countItems; j++)
	{
		line = getLineOfText(position, invoiceText);
		stringstream stringStream2(line);
		stringStream2 >> value1 >> value2 >> c >> invoice.items[j].quantity >> c >> invoice.items[j].price >> c >> invoice.items[j].totalPrice;
		invoice.items[j].article = value1 + value2;
	}/*Unosimo artikal po artikal.Sabiramo dva stringa jer smo glupi da to odradimo odvojeno.*/

	invoice.numItems = countItems;
	double PDV, price, priceToPay;

	line = getLineOfText(position, invoiceText);
	line = getLineOfText(position, invoiceText);/*Sklanjamo red crtica i uzimamo red cijene i ucitavamo je.*/
	stringstream stringStream3(line);
	stringStream3 >> stringValue >> c >> price;

	line = getLineOfText(position, invoiceText);/*Uzimamo red pdv-a i ucitavamo ga.*/
	stringstream stringStream4(line);
	stringStream4 >> stringValue >> c >> PDV;
	
	line = getLineOfText(position, invoiceText);
	stringstream stringStream5(line);
	stringStream5 >> stringValue>>stringValue>>stringValue>>priceToPay; /*Uzimamo red ukupne cijene i ucitavamo je.*/

	return "1";/*Ne znamo sta treba da vrati ali saznacemo.*/
}
void InvoiceParser::RemoveChar(string& str, char c)
{
	string result;
	for (size_t i = 0; i < str.size(); i++)
	{
		char currentChar = str[i];
		if (currentChar != c)
			result += currentChar;
	}
	str = result;
}

string InvoiceParser::parseFormat2(Invoice &invoice, string invoiceText)
{
	return string();
}

string InvoiceParser::parseFormat3(Invoice &invoice, string invoiceText)
{
	return string();
}

string InvoiceParser::parseFormat4(Invoice &invoice, string invoiceText)
{
	return string();
}

string InvoiceParser::parseFormat5(Invoice &invoice, string invoiceText)
{
	return string();
}

int InvoiceParser::moveRows(int rows, int position,string inputText)
{
	int count = 0, i;
	for ( i = position; count < rows; i++)
		if (inputText[i] == '\n')
			count++;
	return i;
}

string InvoiceParser::getLineOfText(int& position, string inputText)
{
	string result;
	for (position; inputText[position] != '\n'; position++)
		result.push_back(inputText[position]);
	position++;
	return result;
}

const string InvoiceParser::racun1 =
"Kupac: ABC\n"
"Datum: 24/10/2017\n"
"\n"
"	       Racun\n"
"\n"
"Proizvod - kolicina - cijena - ukupno\n"
"abc 123  -    10    -    5   -   50\n"
"abb 456  -    20    -   10   -   200\n"
"---------------------------------------\n"
"Ukupno: 250\n"
"PDV: 42.5\n"
"Ukupno za placanje: 292.5 \n";