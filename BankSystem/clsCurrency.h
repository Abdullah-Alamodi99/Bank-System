#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"
#include <string>

using namespace std;

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(Line, Seperator);
		
		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
			stof(vCurrencyData[3]));

	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector<clsCurrency> vCurrencies;
		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);

		if (CurrenciesFile.is_open())
		{
			string DataLine = "";
			while (getline(CurrenciesFile, DataLine))
			{
				clsCurrency CurrencyRecord = _ConvertLineToCurrencyObject(DataLine);
				vCurrencies.push_back(CurrencyRecord);
			}
			CurrenciesFile.close();
		}
		return vCurrencies;
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string CurrencyLine = "";

		CurrencyLine += Currency.Country() + Seperator;
		CurrencyLine += Currency.CurrencyCode() + Seperator;
		CurrencyLine += Currency.CurrencyName() + Seperator;
		CurrencyLine += to_string(Currency.Rate());

		return CurrencyLine;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencies)
	{
		fstream CurrenciesFile;

		string CurrencyLine = "";

		CurrenciesFile.open("Currencies.txt", ios::out);

		if (CurrenciesFile.is_open())
		{
			for (clsCurrency Currency : vCurrencies)
			{
				CurrencyLine = _ConverCurrencyObjectToLine(Currency);
				CurrenciesFile << CurrencyLine << endl;
			}
			CurrenciesFile.close();
		}
		
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}


public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	
	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllLettersInString(CurrencyCode);

		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);//read Mode

		if (CurrenciesFile.is_open())
		{
			string Line;
			while (getline(CurrenciesFile, Line))
			{
				clsCurrency Currency =_ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllLettersInString(Currency.CurrencyCode()) == CurrencyCode)
				{
					CurrenciesFile.close();
					return Currency;
				}
			}

			CurrenciesFile.close();

		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllLettersInString(Country);
		fstream CurrenciesFile;
		CurrenciesFile.open("Currencies.txt", ios::in);//read Mode

		if (CurrenciesFile.is_open())
		{
			string Line;
			while (getline(CurrenciesFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllLettersInString(Currency.Country()) == Country)
				{
					CurrenciesFile.close();
					return Currency;
				}
			}

			CurrenciesFile.close();

		}
		return _GetEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	} 

	float ConvertToOtherCurrency(float Amount, clsCurrency DestinationCurrency)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyCode() == "USD")
		{
			return Amount * DestinationCurrency.Rate();
		}
		if (DestinationCurrency.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return AmountInUSD * DestinationCurrency.Rate();
	}


};

