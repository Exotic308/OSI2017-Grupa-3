#pragma once
#include "Invoice.h"
#include <functional>
#include <vector>
class InvoiceFilter
{
	static std::vector<Invoice> filterInvoice(Invoice*, std::function <bool(Invoice, string)>, int, string); //univerzalna
public:
	static std::vector<Invoice> filter_by_buyer(Invoice*, int, string); // filter prema kupcu kao parametru
	static std::vector<Invoice> filter_by_date(Invoice*, int, string); // filter prema datumu kao parametru
	static std::vector<Invoice> filter_by_name(Invoice*, int, string); // filter prema imenu artikla kao parametru
};