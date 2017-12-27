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
	static string getStringFromFile(const char * path);
	vector<Invoice> invoice_array;
	vector<Invoice> filterValid();
	void scanForNewInvoices();
	Invoice loadFromFile(const char*);
	InvoiceManager();
	~InvoiceManager();
};

