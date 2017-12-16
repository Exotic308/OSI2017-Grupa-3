#pragma once
#include "Message.h"

class InvoiceItem
{
	string article;
	float price, quantity;
public:
	InvoiceItem(string, float, float);//артикал, цијена, квантитет
	float getTotalPrice();
	string hasErrors();
	string getArticle();
	float getPrice();
	float getQuantity();
};

