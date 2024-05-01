#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;

public:
	clsString()
	{
		_Value = "";
	};
	clsString(string Value)
	{
		_Value = Value;
	}

	void setValue(string Value)
	{
		_Value = Value;
	}
	string getValue()
	{
		return _Value;
	}

	_declspec(property(get = getValue, put = setValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}
	short Length()
	{
		Length(_Value);
	}

	static short CountWords(string S1)
	{
		string delim = " ";
		short pos = 0;
		short Counter = 0;
		string sWord;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				Counter++;
			}
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			Counter++;
		}

		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static string UpperFristLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}
			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}
	void UpperFristLetterOfEachWord()
	{
		_Value = UpperFristLetterOfEachWord(_Value);
	}

	static string LowerFristLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}
			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}
	void LowerFristLetterOfEachWord()
	{
		_Value = LowerFristLetterOfEachWord(_Value);
	}

	static string UpperAllLettersInString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}
	void UpperAllLettersInString()
	{
		_Value = UpperAllLettersInString(_Value);
	}

	static string LowerAllLettersInString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}
	void LowerAllLettersInString()
	{
		_Value = LowerAllLettersInString(_Value);
	}

	static char InvertLetterCase(char chr1)
	{
		return isupper(chr1) ? tolower(chr1) : toupper(chr1);
	}

	static string InvertAllLettersCase(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = InvertLetterCase(S1[i]);
		}
		return S1;
	}
	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	static short CountCapitalLetters(string S1)
	{
		short LettersCount = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
				LettersCount++;
		}
		return LettersCount;
	}
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string S1)
	{
		short LettersCount = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
				LettersCount++;
		}
		return LettersCount;
	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}
		return Counter;
	}
	short CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Letter)
	{
		Letter = tolower(Letter);

		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
	}

	static short CountVowels(string S1)
	{
		short Counter = 0;
		for (int i = 0; i < S1.length(); i++)
		{
			if (IsVowel(S1[i]))
				Counter++;
		}

		return Counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static vector<string> Split(string S1, string delim)
	{
		vector<string> vString;
		short pos = 0;
		short Counter = 0;
		string sWord;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			vString.push_back(S1);
		}

		return vString;
	}
	vector<string> Split(string delim)
	{
		return Split(_Value, delim);
	}

	static string TrimLeft(string S1)
	{
		short UntilPos = 0;

		while (S1[UntilPos] == ' ')
		{
			UntilPos++;
		}
		S1.erase(0, UntilPos);

		return S1;
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1)
	{
		short pos = S1.length() - 1;

		while (S1[pos] == ' ')
		{
			pos--;
		}
		S1.erase(++pos, S1.length() - 1);

		return S1;
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return TrimLeft(TrimRight(S1));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vStrings, string Seperate)
	{
		string S1 = "";
		for (string s : vStrings)
		{
			S1 = S1 + s + Seperate;
		}
		return S1.substr(0, S1.length() - Seperate.length());
	}

	static string ReverseString(string S1)
	{
		vector<string> VStrings = Split(S1, " ");
		string S2 = "";

		vector<string>::iterator iter = VStrings.end();

		while (iter != VStrings.begin())
		{
			--iter;
			S2 = S2 + *iter + " ";
		}
		return S2.substr(0, S2.length() - 1);
	}
	void ReverseString()
	{
		_Value = ReverseString(_Value);
	}

	static string ReplaceWordInString(string S1, string WordToReplace, string ReplaceTo)
	{
		short pos = S1.find(WordToReplace);

		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, WordToReplace.length(), ReplaceTo);
			pos = S1.find(WordToReplace);// Find next
		}

		return S1;
	}
	string ReplaceWordInString(string WordToReplace, string ReplaceTo)
	{
		return ReplaceWordInString(_Value, WordToReplace, ReplaceTo);
	}

	static string RemovePunctuations(string S1)
	{
		string S2 = "";
		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
				S2 += S1[i];
		}
		return S2;
	}
	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}

};

