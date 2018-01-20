#pragma once
#include <iostream>
#include <string>
using std::string;

class InvoiceItem
{
public:
	string article;
	float price, quantity, totalPrice;

	InvoiceItem(string= "", float = 0, float = 0, float = 0);
	float getTotalPrice();
	string hasErrors();
	friend std::ostream& operator<<(std::ostream&, const InvoiceItem&);
	bool operator==(InvoiceItem&);
};