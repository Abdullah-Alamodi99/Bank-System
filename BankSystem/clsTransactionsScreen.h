#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen: protected clsScreen
{
private:
	enum enTransactionsMenueOptions
	{
		eDeposit = 1, eWithdraw = 2, eTotalBalance = 3,eTransfer = 4, eShowTransferLog = 5,
		eMainMenue = 6
	};
	
	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]: ";
		short Option = clsInputValidate::ReadShortNumberBetween(1, 6);
		return Option;
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\nPress any key to go back to Transactions Menue ...";
		system("pause>0");
		ShowTransactionsScreen();
	}

	static void _ShowDepositScreen()
	{
		/*cout << "\nDeposit Screen will be here...\n";*/
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		/*cout << "\nWithdraw Screen will be here...\n";*/
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		/*cout << "\nBalances Screen will be here...\n";*/
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _ShowMainScreen()
	{
		
	}

	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
	{
		switch (TransactionsMenueOption)
		{
		case enTransactionsMenueOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eTotalBalance:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eShowTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;
		case enTransactionsMenueOptions::eMainMenue:
			_ShowMainScreen();
			break;
		}
	}


public:
	static void ShowTransactionsScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pTransactions))
		{
			return; // it will exit from this the function
		}

		system("cls");
		_DrawScreenHeader("\t Transactions Screen");

		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t\t Transactions Menue\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "==============================================\n";

		_PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());

	}
};

