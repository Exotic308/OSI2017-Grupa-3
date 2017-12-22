#include "InvoiceItem.h"
#include <iostream>
InvoiceItem::InvoiceItem(string article, float price, float quantity, float totalPrice):
	article(article), price(price), quantity(quantity), totalPrice(totalPrice) {};

float InvoiceItem::getTotalPrice()
{
	return price*quantity;
}

string InvoiceItem::hasErrors()
{
	if (quantity <= 0 || price <= 0)
		return "0Kvantitet ili cijena su negativne vrijednosti";
	else if (getTotalPrice() != totalPrice)
		return "0Kvantitet i cijena se ne poklapaju sa ukupnom cijenom proizvoda";
	else
		return "1Pravilan oblik racuna, unos je moguc";
}

using std::cout;
using std::endl;
void InvoiceItem::print() {
	cout << "Artikal: " << article << endl;
	cout << "Cijena: " << price << endl;
	cout << "Kolicina: " << quantity << endl;
	cout << "Ukupna cijena: " << totalPrice << endl;
	cout << "Izracunata cijena: " << getTotalPrice() << endl;
	cout << "Erori: " << hasErrors() << endl;
}