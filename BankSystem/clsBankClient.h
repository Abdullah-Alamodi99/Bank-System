#pragma once

#include<iostream>
#include "clsPerson.h"
#include "clsString.h";
#include <string>
#include <vector>
#include <fstream>
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	string _PrepareTransferLogRecord(clsBankClient DestinationClient, float Amount,
		string UserName, string Seperator = "#//#")
	{
		string TransferDataLine = "";

		TransferDataLine += clsDate::GetSystemDateTimeString() + Seperator;
		TransferDataLine += AccountNumber() + Seperator;
		TransferDataLine += DestinationClient.AccountNumber() + Seperator;
		TransferDataLine += to_string(Amount) + Seperator;
		TransferDataLine += to_string(AccountBalance) + Seperator;
		TransferDataLine += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferDataLine += UserName;

		return TransferDataLine;
	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		vector<string> vTransferLogLine = clsString::Split(Line, Seperator);
		stTransferLogRecord TransferLogRecord;
		
		TransferLogRecord.DateTime = vTransferLogLine[0];
		TransferLogRecord.sClientAccountNumber = vTransferLogLine[1];
		TransferLogRecord.dClientAccountNumber = vTransferLogLine[2];
		TransferLogRecord.Amount = stof(vTransferLogLine[3]);
		TransferLogRecord.sAccountBalance = stof(vTransferLogLine[4]);
		TransferLogRecord.dAccountBalance = stof(vTransferLogLine[5]);
		TransferLogRecord.UserName = vTransferLogLine[6];

		return TransferLogRecord;
	}

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string> vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode,vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));		
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> _vClients;

		fstream ClientFile;
		ClientFile.open("Clients.txt", ios::in);

		string DataLine;

		if (ClientFile.is_open())
		{

			while (getline(ClientFile, DataLine))
			{
				clsBankClient Client = _ConvertLineToClientObject(DataLine);
				_vClients.push_back(Client);
			}
			ClientFile.close();
		}
		return _vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string DataLine = "";
		DataLine += Client.FirstName + Separator;
		DataLine += Client.LastName + Separator;
		DataLine += Client.Email + Separator;
		DataLine += Client.Phone + Separator;
		DataLine += Client.AccountNumber() + Separator;
		DataLine += Client.PinCode + Separator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	static void _SaveClientsDataTofile(vector<clsBankClient> vClients)
	{
		fstream ClientsFile;

		ClientsFile.open("Clients.txt", ios::out);
		if (ClientsFile.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					ClientsFile << _ConvertClientObjectToLine(C) << endl;
				}
			}
			ClientsFile.close();
		}
	}

	static void _AddDataLineToFile(string DataLine)
	{
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::out | ios::app);

		if (ClientsFile.is_open())
		{
			ClientsFile << DataLine << endl;
			ClientsFile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataTofile(vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _RegisterTransferLog(clsBankClient DestinationClient, float Amount, string UserName)
	{
		string TrasferDataLine = _PrepareTransferLogRecord(DestinationClient, Amount, UserName);

		fstream TransferLogFile;
		TransferLogFile.open("TransferLog.txt", ios::out | ios::app);

		if (TransferLogFile.is_open())
		{
			TransferLogFile << TrasferDataLine << endl;
			TransferLogFile.close();
		}
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{
		string DateTime;
		string sClientAccountNumber;
		string dClientAccountNumber;
		float Amount;
		float sAccountBalance;
		float dAccountBalance;
		string UserName;
	};

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	_declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	_declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;

		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::in);

		if (ClientsFile.is_open())
		{
			string Line = "";
			while (getline(ClientsFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					ClientsFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			ClientsFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;

		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::in);

		if (ClientsFile.is_open())
		{
			string Line = "";
			while (getline(ClientsFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					ClientsFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			ClientsFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		
		return (!Client.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svAccountNumberExists = 2 };
	
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			if (IsClientExist(AccountNumber()))
			{
				return	enSaveResults::svAccountNumberExists;
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

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientsDataTofile(vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}
	
	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}
	bool Transfer(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(DestinationClient, Amount, CurrentUser.UserName);
		return true;
	}

	static vector<stTransferLogRecord> GetTranfersLogList()
	{
		vector<stTransferLogRecord> vTransferLogRecords;
		fstream TransferLogFile;
		TransferLogFile.open("TransferLog.txt", ios::in);

		if (TransferLogFile.is_open())
		{
			string TransferLogLine = "";
			while (getline(TransferLogFile, TransferLogLine))
			{
				stTransferLogRecord TransferLogRecord = _ConvertTransferLogLineToRecord(TransferLogLine);
				vTransferLogRecords.push_back(TransferLogRecord);
			}
			TransferLogFile.close();
		}
		return vTransferLogRecords;
	}

};



