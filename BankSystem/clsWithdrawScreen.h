#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        cout << "Please Enter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t  Withdraw Screen");

        string AccountNumber = "";
        AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] AccountNumber does Not Found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "Enter Withdraw Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\nAre you sure you want to perform this Transaction? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client1.Withdraw(Amount))
            {
                cout << "\nAmount Withdarwed Successfully\n";
                cout << "\nNew Balance = " << Client1.AccountBalance << endl;
            } 
            else
            {
                cout << "\nCannont withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount << endl;
                cout << "Your balance is: " << Client1.AccountBalance << endl;
            }
        }
        else
        {
            cout << "\nOperation was Canceled\n";
        }
    }
};

