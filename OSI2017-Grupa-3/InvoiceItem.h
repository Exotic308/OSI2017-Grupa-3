#pragma once
#include <iostream>
#include <string>
using std::string;

class InvoiceItem
{
public:
	string article,code;
	float price, quantity, totalPrice;
	static float currencyCoefficient;
	InvoiceItem(string= "",string="" , float = 0, float = 0, float = 0);
	float getTotalPrice();
	string hasErrors();
	friend std::ostream& operator<<(std::ostream&, const InvoiceItem&);
	bool operator==(InvoiceItem&);
};