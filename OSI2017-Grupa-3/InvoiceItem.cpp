#include "InvoiceItem.h"
#include "Message.h"
#include <iostream>

using std::cout;
using std::endl;
InvoiceItem::InvoiceItem(string article, float price, float quantity, float totalPrice):
	article(article), price(price), quantity(quantity), totalPrice(totalPrice) {};

/*Metoda koja kompozitno dobija ukupnu cijenu proizvoda.
  Poziva se u funkciji za provjeru errora proizvoda.*/
float InvoiceItem::getTotalPrice()
{
	return price*quantity;
}

/*Metoda koja provjerava da li postoje errori na proizvodu.
  Konstruisana na nacin da se moze jednostavno upotrebljavati
  sa metodama Message klase.*/
string InvoiceItem::hasErrors()
{
	if (quantity <= 0 || price <= 0)
		return "0Kvantitet ili cijena su negativne vrijednosti";
	else if (getTotalPrice() != totalPrice)
		return "0Kvantitet i cijena se ne poklapaju sa ukupnom cijenom proizvoda";
	else
		return "1Pravilan oblik racuna, unos je moguc";
}

std::ostream& operator<<(std::ostream& output, const InvoiceItem& product)
{
	output << "Artikal: " << product.article << endl;
	output << "Cijena: " << product.price << endl;
	output << "Kolicina: " << product.quantity << endl;
	output << "Ukupna cijena: " << product.totalPrice << endl;
	return output;
}


/*Preklopljen operator poredjivanja jednakosti dva elementa.*/
bool InvoiceItem::operator==(InvoiceItem &other)
{
	if (article == other.article && price == other.price && 
		quantity == other.quantity && totalPrice == other.totalPrice) 
		return true;
	return false;
}

