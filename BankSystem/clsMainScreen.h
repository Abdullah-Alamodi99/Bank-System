#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen:protected clsScreen
{
private:

	enum enMainMenueOptions
	{
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
		 eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLoginRegister = 8,
		 eCurrencyExchange = 9, eLogout = 10	
	};

	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do from [1 to 10]: ";
		short Option = clsInputValidate::ReadShortNumberBetween(1, 10);
		return Option;
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\tPress any key to go back to main menue...";
		system("pause>0");
		ShowMainScreen();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		/*cout << "\nAdd New Client Screen will be here...\n";*/
		clsAddNewClientScreen::ShowAddClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		/*cout << "\n Delete Client Screen will be here...\n";*/
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		/*cout << "\nUpdate Client Screen will be here...\n";*/
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		/*cout << "\nFind Client Screen will be here...\n";*/
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		/*cout << "\nTransactions Menue Screen will be here...\n";*/
		clsTransactionsScreen::ShowTransactionsScreen();
	}

	static void _ShowManageUsersMenueScreen()
	{
		/*cout << "\nManage Users Menue Screen will be here...\n";*/
		clsManageUsersScreen::ShowManageUsersMenue();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenueOption(enMainMenueOptions MainMenueOption)
	{
		switch (MainMenueOption)
		{
		case enMainMenueOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eTransactions:
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersMenueScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchangeMainScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eLogout:
			system("cls");
			_Logout();
			break;
		}
	}

public:
	static void ShowMainScreen()
	{
		system("cls");
		_DrawScreenHeader("\t       Main Screen");

		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "================================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[10] Logout.\n";
		cout << setw(37) << left << "" << "================================================\n";

		_PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}
};

