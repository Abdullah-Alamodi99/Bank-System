#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen :protected clsScreen
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
	static void ShowDeleteClientScreen()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return; // it will exit from this the function
        }

        _DrawScreenHeader("\tDelete Client Screen");

        cout << "Please Enter Clinet Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] AccountNumber Not exists, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        _PrintClient(Client);

        cout << "Are you sure you want to delete this client? ";
        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }

    }
};

