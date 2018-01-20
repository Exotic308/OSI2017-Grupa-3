#pragma once
#include"User.h"
#include"Users.h"
#include"Message.h"
#include"Invoice.h"
#include"InvoiceFilter.h"
#include"InvoiceManager.h"
/*U Source fajlu ce biti pozvana metoda koja predstavlja korisnicki interfejs , a zatim ce ona pozivati
druge metode koje su definisane u Meniju*/
class Menu
{
public:
	static void UserUI(InvoiceManager&, Users*);
	static bool requestLogin(Users &, User &);
	static void adminOptions(Users&);
	static void analystOptions(Invoice*);
	static void adminUserControl(Users&);
};
