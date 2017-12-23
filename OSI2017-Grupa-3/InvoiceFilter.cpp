#include "InvoiceFilter.h"

std::vector<Invoice> InvoiceFilter::filterInvoice(Invoice* invoice_array, std::function<bool(Invoice, string)> f, int num_of_elements, string filter)
{
std::vector<Invoice> result;
for (int i = 0; i < num_of_elements; i++) if (f(invoice_array[i], filter)) result.push_back(invoice_array[i]);
return result;
}

std::vector<Invoice> InvoiceFilter::filter_by_buyer(Invoice* invoice_array, int num_of_elements, string buyer)
{
return filterInvoice(invoice_array, [&invoice_array](Invoice x, string filter) {if (!filter.compare(x.buyer)) return true; return false; }, num_of_elements, buyer);
}

std::vector<Invoice> InvoiceFilter::filter_by_date(Invoice* invoice_array, int num_of_elements, string date)
{
return filterInvoice(invoice_array, [&invoice_array](Invoice x, string filter) {if (!filter.compare(x.date)) return true; return false; }, num_of_elements, date);
}

std::vector<Invoice> InvoiceFilter::filter_by_name(Invoice* invoice_array, int num_of_elements, string art_name)
{
return filterInvoice(invoice_array, [&invoice_array](Invoice x, string filter) {for (int i = 0; i < x.numItems; i++) if (!filter.compare(x.items[i].article)) return true; return false; }, num_of_elements, art_name);
}