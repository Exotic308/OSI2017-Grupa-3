#include "Invoice.h"
#include "Message.h"
#define ATOI 0x30
#define EPS 0.1

Invoice::Invoice(int numItems, float price, float PDV, float totalPrice, string buyer, string date) :
	numItems(numItems), price(price),
	PDV(PDV), totalPrice(totalPrice),
	buyer(buyer), date(date),
	items(new InvoiceItem[numItems]) {};

/*Metoda koja izracunava ukupno cijenu sabiranjem cijena zasebnih proizvoda.
  Koristi se u metodi za provjeru errora.*/
float Invoice::getPrice()
{
	float sum = 0;
	for (int i = 0; i < numItems; sum += items[i].totalPrice, i++);
	return sum;
}

/*Nakon sto je racun prosao kroz parser ovdje se vrsi provjera validnosti
  svih detalja nevezanih za format. Return vrijednosti su takve da se mogu
  jednostavno koristiti sa metodama iz Message klase.*/
string Invoice::getErrors()
{
	if (numItems == 0)
		return "0Nije validan racun.";
	if (numItems < 0)
		return "0Broj proizvoda na racunu ne moze biti negativan.";
	if (!properDateFormat(date))
		return "0Neispravan format datuma.";

	//Provjera ispravnosti proizvoda racuna pojedinacno.
	for (int i = 0; i < numItems; i++)
		if (!Message::isSuccess(items[i].hasErrors()))
			return Message::getMessage(items[i].hasErrors());

	float p = getPrice(); 
	if (std::abs(PDV - (price*0.17f))>EPS)
		return "0PDV nije pravilno izracunat";
	if (PDV < 0)
		return "0PDV ne moze imati negativnu vrijednost.";
	if (std::abs(getPrice()-price)>EPS || std::abs(totalPrice - (price + PDV))>EPS)
		return "0Neuskladjena totalna cijena posebnih proizvoda sa totalnom cijenom na racunu.";
	return "1Ispravan racun.";
}

/*Staticka metoda za provjeru ispravnosti formata datuma.*/
bool Invoice::properDateFormat(string date)
{
	if (date.length() != 10)
		return false;

	//Pretvaranje karaktera u prirodne brojeve.
	int day = (date[0] - ATOI) * 10 + date[1] - ATOI;
	int month = (date[3] - ATOI) * 10 + date[4] - ATOI;
	int year = ((date[6] - ATOI) * 1000) + ((date[7] - ATOI) * 100) + ((date[8] - ATOI) * 10) + date[9] - ATOI;

	if (month < 1 || month>12)
		return false;

	//Klasicna provjera validnosti datuma.
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day > 31)
			return false;
		return true;
	case 2:
		if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0))
		{
			if (day > 28)
				return false;
			return true;
		}
	case 4: case 6: case 9: case 11:
		if (day > 30)
			return false;
		return true;
	default:
		return true;
	}
}

/*Preklopljen operator poredjivanja jednakosti dva elementa.*/
bool Invoice::operator==(Invoice &other)
{
	if (numItems == other.numItems && price == other.price && 
		totalPrice == other.totalPrice && PDV == other.PDV && 
		buyer == other.buyer && date == other.date)
	{
		for (int i = 0; i < numItems; i++) 
			if (!(items[i] == other.items[i])) 
				return false;
		return true;
	}
	return false;
}

std::ostream & operator<<(std::ostream& output, const Invoice& bill)
{
	output << "Kupac: " << bill.buyer << std::endl;
	output << "Datum: " << bill.date << std::endl << std::endl;
	output << "Proizvodi" << std::endl;

	for (int i = 0; i < bill.numItems; ++i)
		output << i+1 << ". " << bill.items[i] << std::endl;

	output << std::endl<< "Cijena bez PDV-a: " << bill.price * InvoiceItem::currencyCoefficient << std::endl;
	output << "PDV:" << bill.PDV * InvoiceItem::currencyCoefficient << std::endl;//Pretpostavka je da su sve valute imaj isti PDV
	output << "Cijena + PDV: " << bill.totalPrice * InvoiceItem::currencyCoefficient << std::endl;

	return output;
}
