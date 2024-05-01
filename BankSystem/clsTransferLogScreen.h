#pragma once

#include <iostream>
#include "clsScreen.h"

using namespace std;

class clsTransferLogScreen : clsScreen
{
private:

    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << left << setw(25) << TransferLogRecord.DateTime;
        cout << "| " << left << setw(10) << TransferLogRecord.sClientAccountNumber;
        cout << "| " << left << setw(10) << TransferLogRecord.dClientAccountNumber;
        cout << "| " << left << setw(12) << TransferLogRecord.Amount;
        cout << "| " << left << setw(12) << TransferLogRecord.sAccountBalance;
        cout << "| " << left << setw(12) << TransferLogRecord.dAccountBalance;
        cout << "| " << left << setw(10) << TransferLogRecord.UserName;
    }

public:
	static void ShowTransferLogScreen()
	{
        vector<clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::GetTranfersLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t   ( " + to_string(vTransferLogRecords.size()) + " ) Record(s)";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
        cout << setw(8) << left << "" << "| " << setw(25) << left << "Date/Time";
        cout << "| " << setw(10) << left << "s.Acct";
        cout << "| " << setw(10) << left << "d.Acct";
        cout << "| " << setw(12) << left << "Amount";
        cout << "| " << setw(12) << left << "s.Balance";
        cout << "| " << setw(12) << left << "d.Balance";
        cout << "| " << setw(10) << left << "User";
        cout << setw(8) << left << "" << "\t------------------------------------------------------------------------------------------------------\n";
        if (vTransferLogRecords.size() == 0)
        {
            cout << "\nNo Transfer Recrods available in the system\n";
        }
        else
        {
            for (clsBankClient::stTransferLogRecord TransferLogRecord : vTransferLogRecords)
            {
                _PrintTransferLogRecordLine(TransferLogRecord);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
	}

};

