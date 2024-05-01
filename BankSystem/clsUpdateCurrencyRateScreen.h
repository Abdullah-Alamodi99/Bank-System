#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrencyRateScreen : clsScreen
{
private:
	static float _ReadRate()
	{
		cout << "Enter New Currency Rate: ";
		float NewRate = 0;
		NewRate = clsInputValidate::ReadFloatNumber();

		return NewRate;
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

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		
		_DrawScreenHeader("   Update Currency Rate Screen");

		string CurrencyCode = "";

		cout << "Please Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "Currency is not Found, Choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		_PrintCurrencyCard(Currency);

		cout << "\nAre you sure you want to update Currency Rate? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "\nUpdate Currency Rate:\n";
			cout << "----------------------------\n";

			Currency.UpdateRate(_ReadRate());
			cout << "\nCurrency Rate Updated Successfully\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nOperation was clanceled!\n";
		}

		

	}
};

