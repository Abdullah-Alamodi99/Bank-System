#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static string _ReadCurrencyCode()
	{
		string CurrencyCode = "";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::isCurrencyExist(CurrencyCode))
		{
			cout << "Currency is not Found, Choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}
		CurrencyCode = clsString::UpperAllLettersInString(CurrencyCode);
		return CurrencyCode;
	}

	static float _ReadAmount()
	{
		cout << "\nEnter Amount To Exchange: ";
		float Amount = 0;
		Amount = clsInputValidate::ReadFloatNumber();

		return Amount;
	}

	static void _PrintCurrencyCard(string Title, clsCurrency Currency)
	{
		cout << endl << Title << endl;
		cout << "_______________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_______________________________\n\n";
	}

	static clsCurrency _GetCurrency(string Message)
	{
		cout << Message;
		string CurrencyCode = "";

		CurrencyCode = _ReadCurrencyCode();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;

	}

	static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
	{
		_PrintCurrencyCard("Convert Form:", CurrencyFrom);

		if (CurrencyFrom.CurrencyCode() == "USD")
		{
			float AmountInCurrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
			cout << Amount << " USD = ";
			cout << AmountInCurrency2 << " " << CurrencyTo.CurrencyCode();
			return;
		}

		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = ";
		cout << AmountInUSD << " USD\n";

		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting From USD to: \n";
		_PrintCurrencyCard("To:", CurrencyTo);

		cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = ";
		cout << CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo) << " " << CurrencyTo.CurrencyCode();

	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Answer = 'Y';
		while (toupper(Answer) == 'Y')
		{
			system("cls");

			_DrawScreenHeader("    Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("Please Enter Currency2 Code: ");

			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
			
			cout << "\n\nDo you want to perfrom another calculation (y/n)? ";
			cin >> Answer;
		}
	}
};

