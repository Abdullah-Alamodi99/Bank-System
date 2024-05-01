#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
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
	static void ShowUpdateUserScreen()
	{
        _DrawScreenHeader("\t Update User Screen");

        cout << "Please Enter User Name: ";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "User with [" << UserName << "] UserName does Not exists, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nAre you sure you want to update this user? ";
        char Answer = 'n';
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            cout << "\nUpdate User Info:\n";
            cout << "--------------------\n";

            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResult;
            SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUser::svFaildEmptyObject:
                cout << "\nUser was not saved because It's Empty\n";
                break;

            case clsUser::svSucceeded:
                cout << "\nUser Updated succsessfully\n";
                _PrintUser(User);
                break;
            }
        }
        else
        {
            cout << "\nOperation was canceled!\n";
        }

        
	}
};

