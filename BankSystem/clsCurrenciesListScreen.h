#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
    static void _PrintCurrencyrRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(35) << Currency.Country();
        cout << "| " << left << setw(10) << Currency.CurrencyCode();
        cout << "| " << left << setw(30) << Currency.CurrencyName();
        cout << "| " << left << setw(10) << Currency.Rate();
    }

public:
	static void ShowCurrenciesListScreen()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string Title = "\tCurrencies List Scrren";
		string SubTitle = "\t  ( " + to_string(vCurrencies.size()) + ") Currency(s)";
		_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
        cout << setw(8) << left << "" << "| " << setw(35) << left << "Country";
        cout << "| " << setw(10) << left << "Code";
        cout << "| " << setw(30) << left << "Name";
        cout << "| " << setw(10) << left << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n";
        if (vCurrencies.size() == 0)
        {
            cout << "\nNo Currencies available in the system\n";
        }
        else
        {
            for (clsCurrency Currency : vCurrencies)
            {
                _PrintCurrencyrRecordLine(Currency);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
	}
};

