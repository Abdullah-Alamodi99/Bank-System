#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen: protected clsScreen
{
private:
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
	static void ShowFindClientScreen()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return; // it will exit from this the function
        }

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber = "";

        cout << "Please Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] AccountNumber Not Found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient was not found\n";
        }

        _PrintClient(Client1);
	}
};

