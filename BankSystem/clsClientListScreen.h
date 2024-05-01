#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUser.h"
#include <iomanip>

using namespace std;

class clsClientListScreen :protected clsScreen
{
private:
	static void PrintClientRecordLine(clsBankClient Client)
    {
        cout << "\t" << "| " << left << setw(17) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(15) << Client.Email;
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }


public:
	static void ShowClientsList()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return; // it will exit from this the function
        }
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\tClient List Screen";
        string SubTitle = "\t  (" +  to_string(vClients.size()) + ") Client(s)";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\t----------------------------------------------------------------------------------------------\n";
        cout << "\t" << "| " << setw(17) << left << "Account Number";
        cout << "| " << setw(20) << left << "Client Name";
        cout << "| " << setw(15) << left << "Email";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(10) << left << "Pin Code";
        cout << "| " << setw(12) << left << "Balance";
        cout << "\n\t----------------------------------------------------------------------------------------------\n";
        if (vClients.size() == 0)
        {
            cout << "\nNo clients available in the system\n";
        }
        else
        {
            for (clsBankClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }
        }
        cout << "\t----------------------------------------------------------------------------------------------\n";
    }
};

