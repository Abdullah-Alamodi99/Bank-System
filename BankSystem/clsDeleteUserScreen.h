#pragma once

#include <iostream>
#include "clsUser.h";
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n=====================================\n";
        cout << "User Name  : " << User.UserName << endl;
        cout << "First Name : " << User.FirstName << endl;
        cout << "Last Name  : " << User.LastName << endl;
        cout << "Full Name  : " << User.FullName() << endl;
        cout << "Email      : " << User.Email << endl;
        cout << "Phone      : " << User.Phone << endl;
        cout << "Password   : " << User.Password << endl;
        cout << "Permissions: " << User.Permissions << endl;
        cout << "=====================================\n";
    }

public:
	static void ShowDeleteUserScreen()
	{
        _DrawScreenHeader("\tDelete User Screen");

        cout << "Please Enter UserName: ";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "User with [" << UserName << "] does Not exists, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        cout << "Are you sure you want to delete this User? ";
        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
        else
        {
            cout << "\nOperation was calnceled\n";
        }

	}
};

