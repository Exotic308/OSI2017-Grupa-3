#pragma once
#include "InvoiceItem.h"

class Invoice
{
private:
	float getPrice();
public:
	int numItems;
	float price, totalPrice, PDV;
	string buyer, date;
	InvoiceItem* items;

	Invoice(int = 0, float = 0.0, float = 0.0, float = 0.0, string = "", string = "");
	
	string getErrors();
	friend std::ostream& operator<<(std::ostream&, const Invoice&);
	static bool properDateFormat(string);
	bool operator==(Invoice&);
};

