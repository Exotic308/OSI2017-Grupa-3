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
	static void UserUI(InvoiceManager&, Users*);//metoda koja predstavlja korisnicki interfejs
	static bool requestLogin(Users &, User &);//metoda za prijavu korisnika
	static void adminOptions(Users&);//metoda koja nudi opcije za administratora
	static void analystOptions(Invoice*);//metoda koja nudi opcije za analiticara
	static void adminUserControl(Users&);//metoda za kontrolu koriksnickim nalozima
};
