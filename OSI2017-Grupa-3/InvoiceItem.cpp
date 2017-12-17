#include "InvoiceItem.h"

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