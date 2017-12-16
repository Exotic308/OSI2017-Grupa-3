#pragma once
#include "InvoiceItem.h"

class Invoice
{
private:
	int num_of_invoices;
	InvoiceItem* invoices;
	string buyer, invoiceDate;
public:
	Invoice(int, string, string);
	float getPrice();
	int getPDV();
	int getPriceAndPDV();
	bool properDateFormat();
	string getErrors();
};

