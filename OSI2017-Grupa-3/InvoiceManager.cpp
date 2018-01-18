#include "InvoiceManager.h"
#include <sstream>
#include "Message.h"

InvoiceManager* InvoiceManager::Instance;
bool InvoiceManager::alreadyExists(Invoice& compare)
{
	for (Invoice i : invoice_array) if (i == compare) return true;
	return false;
}

vector<Invoice> InvoiceManager::filterValid()
{
	vector<Invoice> ret;
	for (int i = 0, j=0; i < invoice_array.size(); i++)
	{
		string err = invoice_array[i].getErrors();
		if (err[0] == 1) ret.push_back(invoice_array[j++]);
	}
	return ret;
}

void InvoiceManager::scanForNewInvoices()
{
	string exepath = FileManager::getexepath();
	vector<string> paths = FileManager::GetPathsWithExtension("txt");
	for (int i=0;i<paths.size();i++)
	{
		Invoice tmp = loadFromFile(paths[i].c_str());
		/*if (!alreadyExists(tmp) && Message::isSuccess(tmp.getErrors()))
			std::cout << Message::getMessage(tmp.getErrors());*/
		invoice_array.push_back(tmp);
	}
}

string InvoiceManager::getStringFromFile(const char * path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str() + "\n";
}
Invoice InvoiceManager::loadFromFile(const char * path)
{
	Invoice ret;
	InvoiceParser instanca; //je li metoda pretvorena u staticku?
	std::string str = getStringFromFile(path);
    instanca.parseFromText(ret, str);
	return ret;
}

InvoiceManager::InvoiceManager()
{
	Instance = this;
	scanForNewInvoices();
}

InvoiceManager::~InvoiceManager()
{
	invoice_array.clear();
}
