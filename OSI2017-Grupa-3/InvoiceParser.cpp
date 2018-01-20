#include "InvoiceParser.h"
#include <sstream>
#include "Message.h"
#include <cctype>

#define moveToArticleNameFormat5 28

using std::stringstream;

/*Metode koja prima string (racun ucitan u obliku stringa) i iz njega "izvlaci" podatke i smjesta u klasu invoice.*/
string InvoiceParser::parseFromText(Invoice &invoice, string invoiceText,string fileName)
{
	int format = -1;
	string succes = detectFormat(invoiceText);
	try {
		format = std::stoi(succes);
	}
	catch (const std::exception& e) {
		return "0Neocekivana greska.";
	};
	try {
		switch (format)
		{
		case -1: return "0" + succes;
		case 1: return parseFormat1(invoice, invoiceText);
		case 2: return parseFormat2(invoice, invoiceText);
		case 3: return parseFormat3(invoice, invoiceText);
		case 4: return parseFormat4(invoice, invoiceText);
		case 5: return parseFormat5(invoice, invoiceText,fileName);
		default: return "0Format racuna nije validan.";
		}
	}
	catch(std::exception &e)
	{
		return "0Neocekivana greska.";
	}/*Osiguranje od run-time gresaka.*/
}

/*Metoda koja detektuje koji od formata racuna je u pitanju.*/
string InvoiceParser::detectFormat(string invoiceText)
{
	const int invalidFormat = 0;
	int position = 0;
	string stringValue = getLineOfText(position, invoiceText);
	string temporary, temporary1;

	for (int i = 0; (i < 6)&&(i<(stringValue.length()-1)); i++)
		temporary.push_back(stringValue[i]);/*Pokusa da pokupi "Kupac:" .*/
	
	for (int i = 0; i < 28 && i < invoiceText.length(); i++)
		temporary1.push_back(invoiceText[i]);/*Pokusa da pokupi 5. format.*/

	if (temporary.compare("Kupac:") == 0)/*Format 1 ili 4.*/
	{
		stringstream stringStream2(getLineOfText(position, invoiceText));
		stringStream2 >> stringValue;/*Kupimo "Datum:" .*/

		if (stringValue.compare("Datum:") == 0)
		{
				stringstream stringstreamx(getLineOfText(position, invoiceText));
				stringstream stringStream3(getLineOfText(position, invoiceText));
				stringStream3 >> stringValue;

				if (stringValue.compare("Racun") == 0)
					return "1";/*Detektovan format 1. */
				else if (stringValue.compare("OSI Market"))
					return "4";/*Detektovan format 4.*/
				else
					return "Neprepoznatljiv format(greska u trecem redu).";
		}
		else
			return "Neprepoznatljiv format(greska u prvom redu).";
	}
	else if (stringValue.compare("OSI Market Banja Luka")==0)/*Format 2 ili 3.*/
	{
		stringstream stringStream2(getLineOfText(position, invoiceText));
		stringStream2 >> stringValue;

		if (stringValue.compare("Poslovnica:")==0)
		{
			if (invoiceText[position] == '\n')
				return "2";
			else if (invoiceText[position] == 'K')
			{
				string temporary;
				stringValue = getLineOfText(position, invoiceText);
				for (int i = 0; (i < 6) && (i < (stringValue.length() - 1)); i++)
					temporary.push_back(stringValue[i]);
				if (temporary.compare("Kupac:")==0)
					return "3";
				else
					return "Neprepoznatljiv format(greska u trecem redu).";
			}
			else
				return "Neprepoznatljiv format(greska u trecem redu).";
			
		}
		else
			return "Neprepoznatljiv format(greska u drugom redu).";
	}
	else if (temporary1.compare("Sifra,Kolicina,Cijena,Ukupno")==0)/*Format 5.*/
		return "5";
	else
		return "Neprepoznatljiv format(greska u prvom redu).";/*Nepodrzan format.*/
}
/*Metoda koja izvlaci informacije iz formata racuna broj 1 i smjesta ih u strukturu invoice.*/
string InvoiceParser::parseFormat1(Invoice &invoice, string invoiceText)
{
	int position = 0;
	char c;
	string stringValue, line=getLineOfText(position,invoiceText);

	stringstream stringStream(line);
	stringStream >> stringValue >> invoice.buyer;/*Unosi ime kupca.*/

	line = getLineOfText(position, invoiceText);/*Unosi datum.*/
	stringstream stringStream1(line);
	stringStream1 >> stringValue >> invoice.date;

	for (int i = 0; i<4; i++)
		line = getLineOfText(position, invoiceText);	/*Pomjeramo se na pocetak liste artikala.*/

	int savePosition = position, countItems = 0;
	while (line[0] != '-')
	{
		line = getLineOfText(position, invoiceText);
		countItems++;
	}
	--countItems;
	if (countItems <= 0)
		return "0Nema artikala na racunu.";
	position = savePosition;
	invoice.items = new InvoiceItem[countItems];/*Cuvamo tu poziciju i brojimo koliko ima artikala.*/

	string value1, value2;
	for (int j = 0; j < countItems; j++)
	{
		line = getLineOfText(position, invoiceText);
		stringstream stringStream2(line);
		stringStream2 >> value1 >> value2 >> c >> invoice.items[j].quantity >> c >> invoice.items[j].price >> c >> invoice.items[j].totalPrice;
		invoice.items[j].article = value1;
		invoice.items[j].code = value2;
	}/*Unosimo artikal po artikal.*/
	
	invoice.numItems = countItems;

	line = getLineOfText(position, invoiceText);
	line = getLineOfText(position, invoiceText);/*Sklanjamo red crtica i uzimamo red cijene i ucitavamo je.*/
	stringstream stringStream3(line);
	stringStream3 >> stringValue >> invoice.price;

	line = getLineOfText(position, invoiceText);/*Uzimamo red pdv-a i ucitavamo ga.*/
	stringstream stringStream4(line);
	stringStream4 >> stringValue >> invoice.PDV;

	line = getLineOfText(position, invoiceText);
	stringstream stringStream5(line);
	stringStream5 >> stringValue >> stringValue >> stringValue >> invoice.totalPrice; /*Uzimamo red ukupne cijene i ucitavamo je.*/

	string errors = invoice.getErrors();
	if (!Message::isSuccess(errors))
		return errors;
	return "1";
}
/*Metoda koja uklanja odredjeni char iz stringa.*/
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
/*Metoda koja izvlaci informacije iz formata racuna broj 2 i smjesta ih u strukturu invoice.*/
string InvoiceParser::parseFormat2(Invoice &invoice, string invoiceText)
{
	int position = 0;
	char c;
	string stringValue, temporary;

	for (int i = 0; i < 5; i++)
		getLineOfText(position, invoiceText);/*Pomjeramo se na 6ti red racuna.*/
	
	string line = getLineOfText(position, invoiceText);
	stringstream stringStream(line);
	stringStream >> stringValue >> invoice.buyer;/*Unosi ime kupca.*/

	for (int i = 0; i < 3; i++)
		getLineOfText(position, invoiceText);/*Prelazimo u red sa artiklima.*/

	int savePosition = position, countItems = 0;
	while (stringValue[0] != '-')
	{
		stringValue = getLineOfText(position, invoiceText);
		countItems++;
	}
	countItems--;
	position = savePosition;
	invoice.items = new InvoiceItem[countItems];/*Cuvamo tu poziciju i brojimo koliko ima artikala.*/

	string value1, value2;
	for (int j = 0; j < countItems; j++)
	{
		stringValue = getLineOfText(position, invoiceText);
		stringstream stringStream2(stringValue);
		stringStream2 >> value1 >> value2 >> c >> invoice.items[j].quantity >> c >> invoice.items[j].price >> c >> invoice.items[j].totalPrice;
		invoice.items[j].article = value1;
		invoice.items[j].code=value2;
	}/*Unosimo artikal po artikal*/

	invoice.numItems = countItems;

	stringValue = getLineOfText(position, invoiceText);
	stringValue = getLineOfText(position, invoiceText);
	stringValue = getLineOfText(position, invoiceText);/*Sklanjamo red crtica,red bjeline i uzimamo red cijene i ucitavamo je.*/
	stringstream stringStream3(stringValue);
	stringStream3 >> stringValue >> invoice.price;

	stringValue = getLineOfText(position, invoiceText);/*Uzimamo red pdv-a i ucitavamo ga.*/
	stringstream stringStream4(stringValue);
	stringStream4 >> stringValue >> invoice.PDV;

	stringValue = getLineOfText(position, invoiceText);
	stringstream stringStream5(stringValue);
	stringStream5 >> stringValue >> stringValue >> stringValue >> invoice.totalPrice; /*Uzimamo red ukupne cijene i ucitavamo je.*/

	stringValue = getLineOfText(position, invoiceText);/*Kupimo datum.*/
	stringstream stringStream6(stringValue);
	stringStream6 >> stringValue >> invoice.date;

	string errors = invoice.getErrors();
	if (!Message::isSuccess(errors))
		return errors;

	return "1";
}
/*Metoda koja izvlaci informacije iz formata racuna broj 3 i smjesta ih u strukturu invoice.*/
string InvoiceParser::parseFormat3(Invoice &invoice, string invoiceText)
{
	int position = 0;
	string stringValue;

	getLineOfText(position, invoiceText);
	getLineOfText(position, invoiceText);/*Kupimo dva reda i dolazimo u red gdje se nalazi kupac.*/

	string line = getLineOfText(position, invoiceText);
	stringstream stringStream(line);
	stringStream >> stringValue >> invoice.buyer;/*Unosi ime kupca.*/

	stringValue = getLineOfText(position, invoiceText);
	stringstream stringStream2(stringValue);
	stringStream2 >> stringValue >> invoice.date;/*Kupimo datum.*/

	for (int i = 0; i < 5; i++)
		getLineOfText(position, invoiceText);/*Pomjeramo se na naziv prvog artikla.*/

	int savePosition = position, countItems = 0;
	while (stringValue[0] != '-')
	{
		stringValue = getLineOfText(position, invoiceText);
		countItems++;
	}
	countItems--;
	position = savePosition;
	invoice.items = new InvoiceItem[countItems];/*Cuvamo tu poziciju i brojimo koliko ima artikala.*/

	string value1, value2;
	for (int j = 0; j < countItems; j++)
	{
		stringValue = getLineOfText(position, invoiceText);
		stringValue = turnToGoodFormat(stringValue);
		stringstream stringStream2(stringValue);
		stringStream2 >> value1 >> value2 >> invoice.items[j].quantity >> invoice.items[j].price >> invoice.items[j].totalPrice;
		invoice.items[j].article = value1;
		invoice.items[j].code=value2;
	}/*Unosimo artikal po artikal.*/

	invoice.numItems = countItems;

	stringValue = getLineOfText(position, invoiceText);
	stringValue = getLineOfText(position, invoiceText);
	stringValue = getLineOfText(position, invoiceText);/*Sklanjamo red crtica,sljedeci red i uzimamo red cijene i PDV ucitavamo je.*/
	stringstream stringStream3(stringValue);
	stringStream3 >> stringValue >> invoice.price >> stringValue >> invoice.PDV;

	getLineOfText(position, invoiceText);
	stringValue = getLineOfText(position, invoiceText);
	stringstream stringStream4(stringValue);
	stringStream4 >> stringValue >> stringValue >> stringValue >> invoice.totalPrice;/*Kupimo red praznine pa kupimo red ukupne cijene i ucitavamo je.*/

	string errors = invoice.getErrors();
	if (!Message::isSuccess(errors))
		return errors;

	return "1";

}
/*Metoda koja izvlaci informacije iz formata racuna broj 4 i smjesta ih u strukturu invoice.*/
string InvoiceParser::parseFormat4(Invoice &invoice, string invoiceText)
{
	int position = 0;
	char c;
	string stringValue;

	string line = getLineOfText(position, invoiceText);
	stringstream stringStream(line);
	stringStream >> stringValue >> invoice.buyer;/*Unosi ime kupca.*/

	stringValue = getLineOfText(position, invoiceText);/*Kupimo red sa datumom.*/
	stringstream stringStream2(stringValue);
	stringStream2 >> stringValue >> invoice.date;

	for (int i = 0; i < 5; i++)
		getLineOfText(position, invoiceText);/*Pomjeramo se na naziv prvog artikla.*/

	int savePosition = position, countItems = 0;
	while (stringValue[0] != '-')
	{
		stringValue = getLineOfText(position, invoiceText);
		countItems++;
	}
	countItems--;
	invoice.numItems = countItems;
	position = savePosition;
	invoice.items = new InvoiceItem[countItems];/*Cuvamo tu poziciju i brojimo koliko ima artikala.*/

	string value1, value2;
	for (int j = 0; j < countItems; j++)
	{
		stringValue = getLineOfText(position, invoiceText);
		stringstream stringStream3(stringValue);
		stringStream3 >> value1 >> value2 >> c >> invoice.items[j].quantity >> c >> invoice.items[j].price >> c >> invoice.items[j].totalPrice;
		invoice.items[j].article = value1;
		invoice.items[j].code=value2;
	}/*Unosimo artikal po artikal.*/

	stringValue = getLineOfText(position, invoiceText);
	stringValue = getLineOfText(position, invoiceText);/*Sklanjamo red crtica,i uzimamo red cijene i ucitavamo je.*/
	stringstream stringStream4(stringValue);
	stringStream4 >> stringValue >> invoice.price;

	stringValue = getLineOfText(position, invoiceText);
	stringstream stringStream5(stringValue);
	stringStream5 >> stringValue >> invoice.PDV;/*Ucitavamo red sa PDV i ucitavamo ga.*/

	getLineOfText(position, invoiceText); /*Kupimo red znakova "=" .*/
	stringValue = getLineOfText(position, invoiceText);
	stringstream stringStream6(stringValue);
	stringStream6 >> stringValue >> stringValue >> stringValue >> invoice.totalPrice;/*Kupimo red sa ukupnom cijenom i ucitavamo je.*/

	string errors = invoice.getErrors();
	if (!Message::isSuccess(errors))
		return errors;

	return "1";
}

/*Metoda koja izvlaci informacije iz formata racuna broj 5 i smjesta ih u strukturu invoice.*/
string InvoiceParser::parseFormat5(Invoice &invoice, string invoiceText,string fileName)
{
	string stringValue;
	int position = moveToArticleNameFormat5;
	position++;//sklanjamo \n
	invoice.numItems = getNumberOfItemsFormat5(invoiceText);/*Ovdje mozemo dodati da ispisuje koja je greska,jer u suprotnom metoda vraca samo 0.*/
	invoice.items = new InvoiceItem[invoice.numItems];/*Brojimo artikle i alociramo dovoljno prostora.*/

	for (int i = 0; i < invoice.numItems; i++,position++)
	{
		int j = 0;
		string tempLine = getStringUntilComma(position, invoiceText);/*Kupimo naziv do zapete.*/
		while (std::isalpha(tempLine[j]))
			invoice.items[i].article.push_back(tempLine[j++]);
		while (std::isdigit(tempLine[j]))
			invoice.items[i].code.push_back(tempLine[j++]);
		position++;/*Pomjeramo se sa zapete.*/

		string quantityString, priceString, totalPriceString;
		quantityString = getStringUntilComma(position, invoiceText);
		position++;
		priceString = getStringUntilComma(position, invoiceText);
		position++;
		totalPriceString = getStringOfNumbersUntilLetter(position, invoiceText);/*Kupimo brojnu vrijednost kao string i position ostaje na prvom slovu naziva artikla..*/

		invoice.items[i].quantity = std::stof(quantityString, nullptr);
		invoice.items[i].price = std::stof(priceString, nullptr);
		invoice.items[i].totalPrice = std::stof(totalPriceString, nullptr);/*Konvertujemo iz stringa u float.*/
	}
	int iter = 0;
	while (fileName[iter] != '#')
		invoice.buyer.push_back(fileName[iter++]);
	iter++;
	while (iter < fileName.size() - 4)
		invoice.date.push_back(fileName[iter++]);

	invoice.price = invoice.totalPrice = 0;

	for (int i = 0; i < invoice.numItems; i++)
		invoice.price += invoice.items[i].totalPrice;

	invoice.PDV = invoice.price*0.17f;
	invoice.totalPrice = invoice.PDV+invoice.price;

	string errors = invoice.getErrors();
	if (!Message::isSuccess(errors))
		return errors;

	return "1";

}
/*Metoda koja se pomjera za odredjen broj redova,uzima trenutnu poziciju u stringu i vraca novu poziciju.*/
int InvoiceParser::moveRows(int rows, int position, string inputText)
{
	int count = 0, i;
	for (i = position; count < rows; i++)
		if (inputText[i] == '\n')
			count++;
	return i;
}
/*Metoda koja kupi liniju teksta do znaka \n tj. kupi red teksta iz stringa i azurira poziciju na sljedeci red.*/
string InvoiceParser::getLineOfText(int& position, string inputText)
{
	string result;
	for (position; inputText[position] != '\n'&&(position<(inputText.length()-1)&&(inputText[position]!=EOF)); position++)
		result.push_back(inputText[position]);
	position++;
	return result;
}
/*Metoda koja kupi sve znakove do zapete i azurira poziciju na prvi znak iza zapete.*/
string InvoiceParser::getStringUntilComma(int &position, string inputString)
{
	string result;
	while (inputString[position] != ',')
		result.push_back(inputString[position++]);
	return result;
}

/*Metoda koja racuna broj artikala u formatu 5.*/
int InvoiceParser::getNumberOfItemsFormat5(string inputText)
{
	int countCommas = 0, i = 0;
	while (i != (inputText.size() - 1))
		if (inputText[i++] == ',')
			countCommas++;
	if ((countCommas - 3) % 3 != 0)
		return 0;
	return (countCommas - 3) / 3;
}

/*Metoda koja uklanja znakove izmedju podataka o artiklu i pretvara ih u format povoljan za koristenje stringstream-a.*/
string InvoiceParser::turnToGoodFormat(string inputString)
{
	string result;
	for (int i = 0; i < inputString.size(); i++)
	{
		if (inputString[i] == '=')
			result.push_back(' ');
		else
			result.push_back(inputString[i]);
	}
	return result;
}

/*Metoda koja kupi string brojeva do sljedeceg znaka i azurira poziciju na sljedeci znak.*/
string InvoiceParser::getStringOfNumbersUntilLetter(int &position, string inputText)
{
	string result;
	for (position; ((inputText.size()) != position) && (((inputText[position] >= 0x30) && (inputText[position] <= 0x39)) || (inputText[position] == '.')); position++)
		result.push_back(inputText[position]);
	return result;
}

void InvoiceParser::FormatParserNo5(std::string &str)
{
	str = str.substr(5, str.length());
}

