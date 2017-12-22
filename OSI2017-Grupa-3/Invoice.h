#pragma once
#include "InvoiceItem.h"

class Invoice
{
public:
	int numItems;
	float totalPrice, PDV;
	string buyer, date;
	InvoiceItem* items;

	Invoice(int = 0, float = 0.0, float = 0.0, string = "", string = "");
	float getPrice();
	string getErrors();
	void print();
	static bool properDateFormat(string);
};

