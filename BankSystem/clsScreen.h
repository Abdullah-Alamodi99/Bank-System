#pragma once

#include <iostream>
#include<iomanip>
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << setw(37) << left << "" << "------------------------------------------\n";
		cout << setw(37) << left << "" << "\t" << Title << endl;
		if (SubTitle != "")
		{
			cout << setw(37) << left << "" << "\t" << SubTitle << endl;
		}
		cout << setw(37) << left << "" << "------------------------------------------\n\n";

		cout << setw(37) << left << "" << "User: " << CurrentUser.UserName << endl;
		cout << setw(37) << left << "" << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool _CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermissions(Permission))
		{
			cout << setw(37) << left << "" << "--------------------------------------------\n";
			cout << setw(37) << left << "" << "\t   Access Denied! Contact Your Admin.\n";
			cout << setw(37) << left << "" << "--------------------------------------------\n";
			return false;
		}
		else
		{
			return true;
		}
	}

};

