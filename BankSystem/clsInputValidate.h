#pragma once

#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:

	template <typename T> static T IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if
			(
				(clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
				&&
				(clsDate::IsDateBeforeDate(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
				)
			return true;
		if
			(
				(clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
				&&
				(clsDate::IsDateBeforeDate(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
				)
			return true;
		else
			return false;
	}
	
	static short ReadShortNumber(string Message = "Invalid input, Enter again ")
	{
		short Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Message;
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string Message = "Number is not within the range, Enter again ")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween<short>(Number, From, To))
		{
			cout << Message;
			cin >> Number;
		}
		return Number;
	}

	static int ReadIntNumber(string Message = "Invalid input, Enter again")
	{
		int Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Message << endl;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string Message = "Number is not within the range, Enter again")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween<int>(Number, From, To))
		{
			cout << Message;
			cin >> Number;
		}
		return Number;
	}

	static double ReadDblNumber(string Message = "Invalid input, Enter again")
	{
		double Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Message << endl;
		}
		return Number;
	}

	static int ReadDblNumberBetween(double From, double To, string Message)
	{

		double Number = ReadDblNumber();

		while (!IsNumberBetween<double>(Number, From, To))
		{
			cout << Message;
			cin >> Number;
		}
		return Number;
	}

	static float ReadFloatNumber(string Message = "Invalid input, Enter again")
	{
		float Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Message << endl;
		}
		return Number;
	}

	static string ReadString()
	{
		string S = "";
		getline(cin >> ws, S);

		return S;
	}

	static bool isValidDate(clsDate Date)
	{
		return clsDate::isValidDate(Date);
	}

};



