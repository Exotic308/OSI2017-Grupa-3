#include "InvoiceItem.h"
#include <iostream>
InvoiceItem::InvoiceItem(string article, float price, float quantity, float totalPrice) :article(article), price(price), quantity(quantity), totalPrice(totalPrice) {}

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
void InvoiceItem::print() {
	std::cout << "Artikal: " << article << std::endl;
	std::cout << "Cijena: " << price << std::endl;
	std::cout << "Kolicina: " << quantity << std::endl;
	std::cout << "Ukupna cijena: " << totalPrice << std::endl;
	std::cout << "Izracunata cijena: " << getTotalPrice() << std::endl;
	std::cout << "Erori: " << hasErrors() << std::endl;
}