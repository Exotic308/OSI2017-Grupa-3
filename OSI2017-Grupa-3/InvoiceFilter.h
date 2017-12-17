/*#pragma once
#include "Invoice.h"
#include <functional>
#include <vector>
class InvoiceFilter
{
static std::vector<Invoice> filterInvoice(Invoice*, std::function <bool(Invoice, string)>, int, string); //univerzalna
public:
static std::vector<Invoice> filter_by_buyer(Invoice*, int, string); //kupac
static std::vector<Invoice> filter_by_date(Invoice*, int, string); //datum
static std::vector<Invoice> filter_by_name(Invoice*, int, string); //proizvod
}; */
//koristio sam vector za lakse dodavanje racuna na listu
//ideja je da se preko univerzalne privatne metode ostvare ostale, primaju niz racuna, broj racuna u nizu i parametar filtera
//zasad ostavljam sve komentovano dok se ne dogovorimo o pristupu racunu i zasebnom artiklu
//takodje trebace se i naknadno isprobati da li uopste radi i sa pristupom
//kako sam koristio vector, bilo bi pozeljno da se isti koristi i u fileManager klasi koja sadrzi sve racune