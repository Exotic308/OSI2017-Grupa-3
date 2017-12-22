#include "Invoice.h"
#include "Message.h"
#define ATOI 0x30
using std::cout;
using std::endl;

Invoice::Invoice(int numItems, float totalPrice,float PDV, string buyer, string date) :
	numItems(numItems), totalPrice(totalPrice), PDV(PDV), buyer(buyer), date(date), items(new InvoiceItem[numItems])
		{};

float Invoice::getPrice()
{
	float sum = 0;
	for (int i = 0; i < numItems; sum += items[i].getTotalPrice(), i++);
	return sum;
}

string Invoice::getErrors()
{
	if (numItems < 0)
		return "0Broj proizvoda na racunu ne moze biti negativan.";
	if (!properDateFormat(date))
		return "0Neispravan format datuma.";

	for (int i = 0; i < numItems; i++)
		if (!Message::isSuccess(items[i].hasErrors()))
			return Message::getMessage(items[i].hasErrors());

	if (getPrice() != totalPrice)
		return "0Neuskladjena totalna cijena posebnih proizvoda sa totalnom cijenom na racunu.";
	if (PDV < 0)
		return "0PDV ne moze imati negativnu vrijednost.";

	return "1Ispravan racun.";
}

void Invoice::print() {
	cout << "Kupac: "<< buyer << endl;
	cout << "Datum: " << date << endl<<endl;
	cout << "Itemi" << endl;
	for (int i = 0; i < numItems; ++i) {
		cout << i << ". ";
		items[i].print();
	}
	cout << endl;
	cout << "Izracunata cijena: " << totalPrice<< endl;
	cout << "Izracunat PDV:" << PDV << endl;
	cout << "Izracunata cijena+PDV: " << totalPrice + PDV << endl;
	cout << "Erori: " << Message::getMessage(getErrors()) << endl;
}

bool Invoice::properDateFormat(string date)
{
	if (date.length() != 10)
		return false;
	int day = (date[0] - ATOI) * 10 + date[1] - ATOI;
	int month = (date[3] - ATOI) * 10 + date[4] - ATOI;
	int year = ((date[6] - ATOI) * 1000) + ((date[7] - ATOI) * 100) + ((date[8] - ATOI) * 10) + date[9] - ATOI;

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
