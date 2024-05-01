#pragma once

#include<iostream>
#include "clsUser.h"
#include <iomanip>

using namespace std;

class clsListUsersScreen : protected clsScreen
{
private:
    static void PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << left << setw(17) << User.UserName;
        cout << "| " << left << setw(20) << User.FullName();
        cout << "| " << left << setw(20) << User.Email;
        cout << "| " << left << setw(12) << User.Phone;
        cout << "| " << left << setw(10) << User.Password;
        cout << "| " << left << setw(12) << User.Permissions;
    }

public:
	static void ShowUsersList()
	{
        vector<clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t User List Screen";
        string SubTitle = "\t   (" + to_string(vUsers.size()) + ") User(s)";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
        cout << setw(8) << left << "" << "| " << setw(17) << left << "UserName";
        cout << "| " << setw(20) << left << "Full Name";
        cout << "| " << setw(20) << left << "Email";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(10) << left << "Password";
        cout << "| " << setw(12) << left << "Permissions";
        cout << setw(8) << left << "" << "\n\t------------------------------------------------------------------------------------------------------\n";
        if (vUsers.size() == 0)
        {
            cout << "\nNo Users available in the system\n";
        }
        else
        {
            for (clsUser User : vUsers)
            {
                PrintUserRecordLine(User);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n";
	}
};

