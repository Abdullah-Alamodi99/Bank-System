#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUser.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n=====================================\n";
		cout << "Full Name  : " << Client.FullName() << endl;
		cout << "Acc. Number: " << Client.AccountNumber() << endl;
		cout << "Balance    : " << Client.AccountBalance << endl;
		cout << "=====================================\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";

		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Client with [" << AccountNumber << "] does not exist, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		float Amount = 0;
		cout << "\nEnter Transfer Amount? ";
		cin >> Amount;

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\n\nAmount Exceeds the avialable Balance, Enter another Amount? ";
			cin >> Amount;
		}

		return Amount;
	}

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen");

		cout << "Please Enter Account Number to Transfer From: ";
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);

		cout << "Please Enter Account Number to Transfer To: ";
		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(DestinationClient);

		float Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\n\nAre you sure you want to perform this operation? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild!\n";
			}

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		}
		else
		{
			cout << "\n\nOperation was Canceled\n";
		}
	}
};

