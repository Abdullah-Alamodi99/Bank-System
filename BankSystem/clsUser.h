#pragma once

#include<iostream>
#include "clsPerson.h"
#include "clsString.h";
#include <string>
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	string _PrepareLoginRecord(string Seprator = "#//#")
	{
		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Seprator;
		LoginRecord += UserName + Seprator;
		LoginRecord += clsUtil::EncryptText(Password) + Seprator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string DataLine, string Seperator = "#//#")
	{
		vector <string> LoginRegisterDataLine = clsString::Split(DataLine, Seperator);

		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector<string> vUserData = clsString::Split(Line, Separator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadUsersDataFromFile()
	{
		vector<clsUser> _vUsers;

		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);

		string DataLine;

		if (UsersFile.is_open())
		{

			while (getline(UsersFile, DataLine))
			{
				clsUser User = _ConvertLineToUserObject(DataLine);
				_vUsers.push_back(User);
			}
			UsersFile.close();
		}
		return _vUsers;
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string DataLine = "";

		DataLine += User.UserName + Separator;
		DataLine += User.FirstName + Separator;
		DataLine += User.LastName + Separator;
		DataLine += User.Email + Separator;
		DataLine += User.Phone + Separator;
		DataLine += clsUtil::EncryptText(User.Password) + Separator;
		DataLine += to_string(User.Permissions);

		return DataLine;
	}

	static void _SaveUsersDataTofile(vector<clsUser> vUsers)
	{
		fstream UsersFile;

		UsersFile.open("Users.txt", ios::out);
		if (UsersFile.is_open())
		{
			for (clsUser U : vUsers)
			{
				if (U.MarkedForDelete() == false)
				{
					UsersFile << _ConvertUserObjectToLine(U) << endl;
				}
			}
			UsersFile.close();
		}
	}

	static void _AddDataLineToFile(string DataLine)
	{
		fstream UsersFile;
		UsersFile.open("Users.txt", ios::out | ios::app);

		if (UsersFile.is_open())
		{
			UsersFile << DataLine << endl;
			UsersFile.close();
		}
	}

	void _Update()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataTofile(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

public:

	enum enPermissions { 
		pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
		pLoginRegister = 128};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string UserName, string FirstName, string LastName, string Email,
		string Phone,string Password, int Permissions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	void SetUserName(string Username)
	{
		_UserName = Username;
	}
	string GetUserName()
	{
		return _UserName;
	}
	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	_declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	void RegisterLogin()
	{
		string LoginRecord = _PrepareLoginRecord();
		fstream LoginRegister;
		LoginRegister.open("LoginRegister.txt", ios::out | ios::app);

		if (LoginRegister.is_open())
		{
			LoginRegister << LoginRecord << endl;
			LoginRegister.close();
		}
	}

	static clsUser Find(string UserName)
	{
		vector<clsUser> vUsers;

		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);

		if (UsersFile.is_open())
		{
			string Line = "";
			while (getline(UsersFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					UsersFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			UsersFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		vector<clsUser> vUsers;

		fstream UsersFile;
		UsersFile.open("Users.txt", ios::in);

		if (UsersFile.is_open())
		{
			string Line = "";
			while (getline(UsersFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName== UserName && User.Password == Password)
				{
					UsersFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			UsersFile.close();
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
			break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;

		case enMode::AddNewMode:
			if (IsUserExist(_UserName))
			{
				return	enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, UserName, "", "", "", "", "", 0);
	}

	static vector<stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector<stLoginRegisterRecord> LoginRegisterRecords;

		fstream LoginRegisterFile;
		LoginRegisterFile.open("LoginRegister.txt", ios::in);

		if (LoginRegisterFile.is_open())
		{
			string DataLine = "";
			while (getline(LoginRegisterFile, DataLine))
			{
				stLoginRegisterRecord Record = _ConvertLoginRegisterLineToRecord(DataLine);
				LoginRegisterRecords.push_back(Record);
			}
			LoginRegisterFile.close();
		}
		return LoginRegisterRecords;
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U._MarkedForDelete = true;
				break;
			}
		}
		_SaveUsersDataTofile(vUsers);
		*this = _GetEmptyUserObject();

		return true;
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::pAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;

		else
			return false;
	}
};

