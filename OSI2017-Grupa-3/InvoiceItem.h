#pragma once
#include <string>
using std::string;

class InvoiceItem
{
public:
	string article;
	float price, quantity, totalPrice;

	InvoiceItem(string = 0, float = 0, float = 0, float = 0);//artikal, cijena, kvantitet i ukupna cijena za provjeru
	float getTotalPrice();
	string hasErrors();
};