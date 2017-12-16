#include "Invoice.h"

Invoice::Invoice(int num_of_invoices, string buyer, string invoiceDate) :num_of_invoices(num_of_invoices), buyer(buyer), invoiceDate(invoiceDate), invoices(new InvoiceItem[num_of_invoices]) {}

float Invoice::getPrice()
{
	float sum = 0;
	for (int i = 0; i < num_of_invoices; sum += invoices[i].getTotalPrice(), i++);
	return sum;
}

int Invoice::getPDV()
{
	return getPrice()*0.17;
}

int Invoice::getPriceAndPDV()
{
	return getPrice() + getPDV();
}

bool Invoice::properDateFormat()
{
	if (invoiceDate.length() != 11)
		return "0Neispravan format datuma";
	int day = (invoiceDate[0] - 0x30) * 10 + invoiceDate[1], month = (invoiceDate[3] - 0x30) * 10 + invoiceDate[4];
	int year = (invoiceDate[6] * 1000) + (invoiceDate[7] * 100) + (invoiceDate[8] * 10) + invoiceDate[9];
	
	if ((day == 0 || day > 31) || (month == 0 || month > 12))
		return "0Neispravan format datuma";

}

string Invoice::getErrors()
{
	
}

