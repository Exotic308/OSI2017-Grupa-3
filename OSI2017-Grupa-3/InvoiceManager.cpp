#include "InvoiceManager.h"
#include <sstream>
#include "Message.h"

/*Staticka instanca (singleton) InvoiceManager-a.*/
InvoiceManager* InvoiceManager::Instance;

/*Provjera vec postojuceg racuna u nizu.*/
bool InvoiceManager::alreadyExists(Invoice& compare)
{
	for (Invoice i : invoice_array) if (i == compare) return true;
	return false;
}

/*Funkcija za filtriranje validnih racuna u nizu.*/
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


/*Funkcija za skeniranje novih racuna u okruzenju aplikacije.*/
void InvoiceManager::scanForNewInvoices()
{
	vector<string> paths = FileManager::GetPathsWithExtension("txt");
	vector<string> paths_csv= FileManager::GetPathsWithExtension("csv");
	for (int i = 0; i < paths_csv.size(); i++) paths.push_back(paths_csv[i]);
	for (int i=0;i<paths.size();i++)
	{
		Invoice tmp = loadFromFile(paths[i].c_str());
		std::string message = tmp.getErrors();
		string invoice_count=std::to_string(i+1);
		if (!Message::isSuccess(message))
		{ 
			invoice_array_invalid.push_back(tmp); 
			FileManager::saveToFolder("Invalidni", "racun"+invoice_count+"_error.txt", getStringFromFile(paths[i].c_str()));
		}
		else 
		{
			invoice_array.push_back(tmp);
			FileManager::saveToFolder("Validni", "racun" + invoice_count + ".txt", getStringFromFile(paths[i].c_str()));
		}
		std::cout << Message::getMessage(message) << std::endl;
	}
	
		
}

/*Funkcija koja ucitava sadrzaj datoteke u obliku string-a.*/
string InvoiceManager::getStringFromFile(const char * path) {
	std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str() + "\n";
}

/*Funkcija koja ucitava podatak iz odgovarajuceg fajla te ga cuva u obliku Invoice-a.*/
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