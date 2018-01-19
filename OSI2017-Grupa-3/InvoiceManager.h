#pragma once
#include "FileManager.h"
#include "Invoice.h"
#include "InvoiceParser.h"
#include <vector>
#include <fstream>
using std::vector;

class InvoiceManager
{
	bool alreadyExists(Invoice&); //provjera vec postojuceg racuna u nizu
public:
	static InvoiceManager *Instance; //staticka instanca (singleton) InvoiceManager-a
	static string getStringFromFile(const char * path); //funkcija koja ucitava sadrzaj datoteke u obliku string-a
	vector<Invoice> invoice_array; //niz racuna
	vector<Invoice> filterValid(); //funkcija za filtriranje validnih racuna u nizu
	void scanForNewInvoices(); //funkcija za skeniranje novih racuna u okruzenju aplikacije
	Invoice loadFromFile(const char*); //funkcija koja ucitava podatak iz odgovarajuceg fajla te ga cuva u obliku Invoice-a
	InvoiceManager(); //konstruktor
	~InvoiceManager(); //destruktor
};

