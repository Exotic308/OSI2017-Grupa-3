#include "InvoiceItem.h"

InvoiceItem::InvoiceItem(string article, float price, float quantity, float totalPrice) :article(article), price(price), totalPrice(totalPrice) {}

float InvoiceItem::getTotalPrice()
{
	return price*quantity;
}

string InvoiceItem::hasErrors()
{
	if (quantity <= 0 || price <= 0)
		return "0Неисправан облик рачуна";
	else if (getTotalPrice() != totalPrice)
		return "0Квантитет и цијена се не поклапају са укупном цијеном написаном на рачуну";
	else
		return "1Правилан облик рачуна, рачун је могуће учитати";
}

string InvoiceItem::getArticle()
{
	return article;
}

float InvoiceItem::getPrice()
{
	return price;
}

float InvoiceItem::getQuantity()
{
	return quantity;
}
