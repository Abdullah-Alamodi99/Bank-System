#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:

	enum enCharType {
		SmallLetter = 1, CapitalLetter = 2,
		Digit = 3, MixChars = 4, SpecialCharacter = 5
	};

	static void Srand()
	{
		srand((unsigned)time(NULL));

	}

	static int RandomNumber(int From, int To)
	{
		int randNum = rand() % (To - From + 1) + From;

		return randNum;
	}

	static char GetRandomCharacter(enCharType Random)
	{
		if (Random == enCharType::MixChars)
		{
			Random = (enCharType)RandomNumber(1, 3);
		}

		switch (Random)
		{
		case enCharType::SmallLetter:
			return char(RandomNumber(97, 122));

		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));

		case enCharType::SpecialCharacter:
			return char(RandomNumber(33, 47));

		case enCharType::Digit:
			return char(RandomNumber(48, 57));

		defualt:
			{
				return char(RandomNumber(65, 90));
				break;
			}
		}

	}

	static string EncryptText(string Text, short EncriptionKey = 2)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char(int(Text[i]) + EncriptionKey);

		}
		return Text;
	}

	static string DecryptText(string Text, short EncriptionKey = 2)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char(int(Text[i]) - EncriptionKey);

		}
		return Text;
	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word = "";
		for (int i = 1; i <= Length; i++)
		{
			Word += char(GetRandomCharacter(CharType));
		}

		return Word;
	}

	static string GenerateKey(enCharType CharType = CapitalLetter)
	{
		return GenerateWord(CharType, 4) + "-"
			+ GenerateWord(CharType, 4) + "-"
			+ GenerateWord(CharType, 4) + "-"
			+ GenerateWord(CharType, 4);
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key [" << i << "] : ";
			cout << GenerateKey(CharType) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int Array[100], int& arrLength, short From, short To)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Array[i] = RandomNumber(From, To);
		}
	}

	static int MaxNumberInArray(int arr[100], int arrLength)
	{
		int Max = 0;
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] > Max)
			{
				Max = arr[i];
			}
		}

		return Max;
	}

	static int MinNumberInArray(int arr[100], int arrLength)
	{
		int Min = 0;
		Min = arr[0];
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] < Min)
			{
				Min = arr[i];
			}
		}

		return Min;
	}

	static int SumArray(int arr[100], int arrLength)
	{
		int Sum = 0;
		for (int i = 0; i < arrLength; i++)
		{
			Sum += arr[i];
		}

		return Sum;
	}

	static float ArrayAverage(int arr[100], int arrLength)
	{
		return (float)SumArray(arr, arrLength) / arrLength;
	}

	static void SumOf2Arrays(int arr1[100], int arr2[100], int arr3[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			arr3[i] = arr1[i] + arr2[i];
		}
	}

	static void Swap(int& A, int& B)
	{
		int Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(float& A, float& B)
	{
		float Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(double& A, double& B)
	{
		double Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& S1, string& S2)
	{
		string Temp;
		Temp = S1;
		S1 = S2;
		S2 = Temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate::SwapDates(Date1, Date2);
	}

	static void ShuffleArray(int Array[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(Array[RandomNumber(1, arrLength) - 1], Array[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(string Array[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(Array[RandomNumber(1, arrLength) - 1], Array[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(clsDate Array[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			Swap(Array[RandomNumber(1, arrLength) - 1], Array[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void FillArrayWithRandomKeys(string ArrayOfKeys[100], int& arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			ArrayOfKeys[i] = GenerateKey();
		}
	}

	static void FillArrayWithRandomWords(string ArrayOfWords[100], int& arrLength, enCharType CharType, short WordLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			ArrayOfWords[i] = GenerateWord(CharType, WordLength);
		}
	}

	static int GetElementPositionInArray(int Number, int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] == Number)
			{
				return i;
			}
		}

		return -1;
	}

	static int GetElementPositionInArray(string Element, string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] == Element)
			{
				return i;
			}
		}

		return -1;
	}

	static bool IsElementFoundInArray(int Number, int arr[100], int arrLength)
	{
		return GetElementPositionInArray(Number, arr, arrLength) != -1;
	}

	static bool IsElementFoundInArray(string Element, string arr[100], int arrLength)
	{
		return GetElementPositionInArray(Element, arr, arrLength) != -1;
	}

	static bool IsPalindromeArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] != arr[arrLength - i - 1])
				return false;
		}
		return true;
	}

	static bool IsPalindromeArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] != arr[arrLength - i - 1])
				return false;
		}
		return true;
	}

	static int PositiveCount(int Array[100], int arrLength)
	{
		int Count = 0;
		for (int i = 0; i < arrLength; i++)
		{
			if (Array[i] >= 0)
				Count++;
		}

		return Count;
	}

	static int NegativeCount(int Array[100], int arrLength)
	{
		int Count = 0;
		for (int i = 0; i < arrLength; i++)
		{
			if (Array[i] < 0)
				Count++;
		}

		return Count;
	}

	static string Taps(short NumberOfTaps)
	{
		string Taps = "";
		for (short i = 0; i < NumberOfTaps; i++)
		{
			Taps += "\t";
		}
		return Taps;
	}

	static string NumberToText(int Number)
	{
		if (Number == 0)
		{
			return "";
		}
		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
							   "Ten", "Eleven","Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen","Seventeen",
							   "Eighteen", "Ninteen" };
			return arr[Number] + " ";
		}
		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "", "","Twinty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninty" };
			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}
		if (Number >= 100 && Number <= 199)
		{
			return "One Hunderd " + NumberToText(Number % 100);
		}
		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + "Hudreds " + NumberToText(Number % 100);
		}
		if (Number >= 1000 && Number <= 1999)
		{
			return " One Thousand " + NumberToText(Number % 1000);
		}
		if (Number >= 2000 && Number <= 999999)
		{
			return  NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}
		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}
		if (Number >= 2000000 && Number <= 999999999)
		{
			return  NumberToText(Number / 1000000) + " Milions " + NumberToText(Number % 1000000);
		}
		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Bilion " + NumberToText(Number % 1000000000);
		}

		else
		{
			return  NumberToText(Number / 1000000000) + " Bilions " + NumberToText(Number % 1000000000);
		}

	}

};
