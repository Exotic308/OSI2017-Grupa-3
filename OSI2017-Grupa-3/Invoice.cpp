#include "Invoice.h"
#include "Message.h"
#define ATOI 0x30

Invoice::Invoice(int num, string buyer, string date) :numItems(num), buyer(buyer), date(date), items(new InvoiceItem[numItems])
{};

float Invoice::getPrice()
{
	float sum = 0;
	for (int i = 0; i < numItems; sum += items[i].getTotalPrice(), i++);
	return sum;
}

float Invoice::getPDV()
{
	return getPrice()*0.17f;
}

float Invoice::getPriceAndPDV()
{
	return getPrice() + getPDV();
}

bool Invoice::properDateFormat()
{
	if (date.length() != 10)
		return false;
	int day = (date[0] - ATOI) * 10 + date[1] - ATOI;
	int month = (date[3] - ATOI) * 10 + date[4] - ATOI;
	int year = ((date[6]- ATOI )* 1000) + ((date[7]- ATOI) * 100) + ((date[8]- ATOI) * 10) + date[9] - ATOI;
	
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

string Invoice::getErrors()
{
	Message a;
	if (!properDateFormat())
		return "0Neispravan format datuma.";
	if (numItems < 0)
		return "0Broj proizvoda na racunu ne moze biti negativan.";
	for (int i = 0; i < numItems; i++)
		if (Message::isSuccess(items[i].hasErrors()))
			return "0Netacan oblik proizvoda na racunu.";
	return "1Ispravan racun.";
}
