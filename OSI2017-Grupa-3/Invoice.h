#pragma once
#include "InvoiceItem.h"

class Invoice
{
public:
	int numItems;
	string buyer, date;
	InvoiceItem* items;

	Invoice(int, string, string);
	float getPrice();
	float getPDV();
	float getPriceAndPDV();
	bool properDateFormat();
	string getErrors();
};

