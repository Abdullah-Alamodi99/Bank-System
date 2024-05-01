#pragma once

#include <iostream>
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
#include <fstream>

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginsCount = 0;

		string UserName, Password;
		do
		{
			if (LoginFaild)
			{
				FaildLoginsCount++;
				cout << "\nInvalid Username/Password!\n";
				cout << "You have " << 3 - FaildLoginsCount << " Trial(s) to login.\n";
			}
			if (FaildLoginsCount == 3)
			{
				cout << "\n\nYou are locked after 3 faild trials\n";
				return false;
			}

			cout << "\nPlease Enter Username: ";
			getline(cin >> ws, UserName);

			cout << "Please Enter Password: ";
			getline(cin, Password);

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainScreen();
		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		return _Login();
	}
};

