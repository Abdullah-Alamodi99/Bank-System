#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:

	enum CurrencyExchanageMenueOptions
	{ eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3 , eCurrencyCalculator = 4, eMainMenue = 5};

	static short _ReadCurrencyExchanageMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]: ";
		short Option = clsInputValidate::ReadShortNumberBetween(1, 5);
		return Option;
	}

	static void _GoBackToCurrencyExchanageMenue()
	{
		cout << "\nPress any key to go back to Currency Exchange Menue ...";
		system("pause>0");
		ShowCurrenciesMenue();
	}

	static void _ShowCurrenciesListScreen()
	{
		/*cout << "\nCurrencies List will be here...\n";*/
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		/*cout << "\nFind Currency Screen will be here...\n";*/
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		/*cout << "\nUpdate Rate Screen will be here...\n";*/
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		/*cout << "\nCurrency Calculator Screen will be here...\n";*/
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyExchangeMenueOption(CurrencyExchanageMenueOptions Option)
	{
		switch (Option)
		{
		case CurrencyExchanageMenueOptions::eListCurrencies:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyExchanageMenue();
			break;
		case CurrencyExchanageMenueOptions::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchanageMenue();
			break;
		case CurrencyExchanageMenueOptions::eUpdateRate:
			system("cls");
		_ShowUpdateRateScreen();
			_GoBackToCurrencyExchanageMenue();
			break;
		case CurrencyExchanageMenueOptions::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchanageMenue();
			break;
		case CurrencyExchanageMenueOptions::eMainMenue:
		{

		}
		}
	}

public:
	static void ShowCurrenciesMenue()
	{
		system("cls");
		_DrawScreenHeader("    Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\t Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "==============================================\n";

		_PerformCurrencyExchangeMenueOption((CurrencyExchanageMenueOptions)_ReadCurrencyExchanageMenueOption());
	}
};

