#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
        {
            cout << "Enter First Name: ";
            User.FirstName = clsInputValidate::ReadString();

            cout << "Enter Last Name: ";
            User.LastName = clsInputValidate::ReadString();

            cout << "Enter Email: ";
            User.Email = clsInputValidate::ReadString();

            cout << "Enter Phone: ";
            User.Phone = clsInputValidate::ReadString();

            cout << "Enter Password: ";
            User.Password = clsInputValidate::ReadString();

            User.Permissions = _ReadPermissions();
        }

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

    static int _ReadPermissions()
    {
        char Answer = 'n';
        int Permissions = 0;

        cout << "\n\nDo you want to give full access y/n? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            return -1;
        }
        else
        {
            cout << "\n\nDo you want to give access to: \n\n";

            cout << "Show Client List? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pListClients;
            }

            cout << "\n\nAdd New Client? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pAddNewClient;
            }

            cout << "\n\nDelete Client? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pDeleteClient;
            }

            cout << "\n\nUpdate Client? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pUpdateClient;
            }

            cout << "\n\nFind Client? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pFindClient;
            }

            cout << "\n\nTransactions? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pTransactions;
            }

            cout << "\n\nManage Users? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pManageUsers;
            }

            cout << "\n\nShow Login Register? (y/n)? ";
            cin >> Answer;
            if (toupper(Answer) == 'Y')
            {
                Permissions += clsUser::enPermissions::pLoginRegister;
            }

            return Permissions;
        }
    }

public:
	static void ShowAddNewUserScreen()
	{
        _DrawScreenHeader("\tAdd New User Screen");

        cout << "Please Enter User Name: ";
        string UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "User with [" << UserName << "] already exists, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        cout << "\nAdd New User\n";
        cout << "--------------------\n";

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case clsUser::svFaildEmptyObject:
            cout << "\nUser was not saved because It's Empty\n";
            break;
        case clsUser::svFaildUserExists:
            cout << "User was not saved because It's Already Exists";
            break;
        case clsUser::svSucceeded:
            cout << "\nUser Added succsessfully\n";
            _PrintUser(NewUser);
            break;
        }
	}
};

