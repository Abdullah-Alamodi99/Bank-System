#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen: protected clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "Enter First Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter Last Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n=====================================\n";
        cout << "First Name : " << Client.FirstName << endl;
        cout << "Last Name  : " << Client.LastName << endl;
        cout << "Full Name  : " << Client.FullName() << endl;
        cout << "Email      : " << Client.Email << endl;
        cout << "Phone      : " << Client.Phone << endl;
        cout << "Acc. Number: " << Client.AccountNumber() << endl;
        cout << "Password   : " << Client.PinCode << endl;
        cout << "Balance    : " << Client.AccountBalance << endl;
        cout << "=====================================\n";
    }

public:
	static void ShowUpdateClientScreen()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClient))
        {
            return; // it will exit from this the function
        }

        _DrawScreenHeader("\t Update Client Screen");

        string AccountNumber = "";

        cout << "Please Enter Clinet Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] AccountNumber Not Found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "Are you sure you want to update this client? ";
        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            cout << "\n\nUpdate Client Info:\n";
            cout << "--------------------\n";

            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResults::svSucceeded:
                cout << "\nClient Updated succsessfully\n";
                _PrintClient(Client1);
                break;
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "\nClient was not saved because It's Empty\n";
                break;
            }
        }
	}
};

