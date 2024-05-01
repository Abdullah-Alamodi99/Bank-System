#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen :protected clsScreen
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
	static void ShowAddClientScreen()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return; // it will exit from this the function
        }

        _DrawScreenHeader("\tAdd New Client Screen");

        cout << "Please Enter Clinet Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] AccountNumber already exists, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        cout << "\nAdd New Client\n";
        cout << "--------------------\n";

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::svFaildEmptyObject:
            cout << "\nClient was not saved because It's Empty\n";
            break;
        case clsBankClient::svAccountNumberExists:
            cout << "Client was not saved because It's Already Exists";
            break;
        case clsBankClient::svSucceeded:
            cout << "\nClient Added succsessfully\n";
            _PrintClient(NewClient);
            break;
        }
	}
};

