#pragma once
#include"User.h"
#include"Users.h"
#include"Message.h"
#include"Invoice.h"
#include"InvoiceFilter.h"
class Menu
{
public:
	static bool requestLogin(Users &, User &);
	static void adminOptions();
	static void analystOptions(Invoice*);
};
