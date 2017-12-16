#pragma once
#include "Message.h"

class InvoiceItem
{
	string article;
	float price, quantity, totalPrice;
public:
	InvoiceItem(string, float, float, float);//артикал, цијена, квантитет
	float getTotalPrice();
	string hasErrors();
	string getArticle();
	float getPrice();
	float getQuantity();
};