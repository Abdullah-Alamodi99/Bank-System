#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void PrintLoginRecordLine(clsUser::stLoginRegisterRecord LoginRecord)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << LoginRecord.DateTime;
        cout << "| " << left << setw(20) << LoginRecord.UserName;
        cout << "| " << left << setw(20) << LoginRecord.Password;
        cout << "| " << left << setw(12) << LoginRecord.Permissions;
    }

public:
	static void ShowLoginRegisterScreen()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return; // it will exit from this the function
        }
		vector<clsUser::stLoginRegisterRecord> vLoginRecords = clsUser::GetLoginRegisterList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t  ( " + to_string(vLoginRecords.size()) + " ) Record(s)";

		_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
        cout << setw(8) << left << "" << "| " << setw(30) << left << "Date/Time";
        cout << "| " << setw(20) << left << "UserName";
        cout << "| " << setw(20) << left << "Password";
        cout << "| " << setw(12) << left << "Permissions";
        cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n";
        if (vLoginRecords.size() == 0)
        {
            cout << "\nNo Login Recrods available in the system\n";
        }
        else
        {
            for (clsUser::stLoginRegisterRecord LoginRecord : vLoginRecords)
            {
                PrintLoginRecordLine(LoginRecord);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
	}
};

