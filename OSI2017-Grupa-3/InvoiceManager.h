#pragma once
#include "FileManager.h"
#include "Invoice.h"
#include "InvoiceParser.h"
#include <vector>
#include <fstream>
using std::vector;

class InvoiceManager
{
	bool alreadyExists(Invoice&); 
public:
	static InvoiceManager *Instance; 
	static string getStringFromFile(const char * path); 
	vector<Invoice> invoice_array; //niz racuna
	vector<Invoice> invoice_array_invalid; //niz racuna sa greskom
	vector<Invoice> filterValid(); 
	void scanForNewInvoices(); 
	Invoice loadFromFile(const char*); 
	InvoiceManager(); //konstruktor
	~InvoiceManager(); //destruktor
};

