#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsFindCurrencyScreen : clsScreen
{
	enum enFindCurrencyBy { Code = 1, Country = 2 };

	static short _ReadFindCurrencyOption()
	{
		cout << "Find By: [1] Code or [2] Country? ";
		short Option = clsInputValidate::ReadShortNumberBetween(1, 2);

		return Option;
	}

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card: \n";
		cout << "_______________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_______________________________\n";
	}

	static void _FindCurrencyByCode()
	{
		cout << "\nPlease Enter CurrencyCode: ";
		string CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrecny Found :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrecny Not Found :-(\n";
		}
	}

	static void _FindCurrencyByCountry()
	{
		cout << "\nPlease Enter Country: ";
		string Country = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCountry(Country);

		if (!Currency.IsEmpty())
		{
			cout << "\nCurrecny Found :-)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrecny Not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");

		enFindCurrencyBy Option = (enFindCurrencyBy)_ReadFindCurrencyOption();
		
		switch (Option)
		{
		case enFindCurrencyBy::Code:
			_FindCurrencyByCode();
			break;

		case enFindCurrencyBy::Country:
			_FindCurrencyByCountry();
			break;
		}	
	}
};

