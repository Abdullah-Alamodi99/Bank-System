#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:  
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(17) << left << "" << "| " << left << setw(17) << Client.AccountNumber();
        cout << "| " << left << setw(25) << Client.FullName();
        cout << "| " << left << setw(10) << Client.AccountBalance;
    }

public:
    static void ShowTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t Balances List Screen";
        string SubTitle = "\t   ( " + to_string(vClients.size()) + " ) Client(s)";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(17) << "" << "---------------------------------------------------------------------------------\n";
        cout << setw(17) << "" << "| " << setw(17) << left << "Account Number";
        cout << "| " << setw(25) << left << "Client Name";
        cout << "| " << setw(10) << left << "Balance";
        cout << endl << setw(17) << "" << "---------------------------------------------------------------------------------\n";

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
        {
            cout << "\nNo clients available in the system\n";
        }
        else
        {
            for (clsBankClient Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }
        }
        cout << setw(17) << "" << "--------------------------------------------------------------------------------\n\n";

        cout << "\t\t\t\t\t        Total Balances = " << TotalBalances << endl;
        cout << "\t\t\t\t\t        ( " << clsUtil::NumberToText(TotalBalances) << ")\n";
    }

};

