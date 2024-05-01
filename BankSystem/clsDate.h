#pragma once

#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;

	clsDate GetDateFromDaysOrderInYear(short DaysOrderInYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DaysOrderInYear;
		short MonthDays = 0;
		Date.Month = 1;
		Date.Year = Year;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	clsDate(string Date)
	{
		vector<string> vStringDate = clsString::Split(Date, "/");

		_Day = stoi(vStringDate[0]);
		_Month = stoi(vStringDate[1]);
		_Year = stoi(vStringDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short Days, short Year)
	{
		clsDate Date = GetDateFromDaysOrderInYear(Days, Year);

		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}

	void setDay(short Day)
	{
		_Day = Day;
	}
	short getDay()
	{
		return _Day;
	}

	_declspec(property(get = getDay, put = setDay)) short Day;

	void setMonth(short Month)
	{
		_Month = Month;
	}
	short getMonth()
	{
		return _Month;
	}
	_declspec(property(get = getMonth, put = setMonth)) short Month;

	void setYear(short Year)
	{
		_Year = Year;
	}
	short getYear()
	{
		return _Year;
	}

	_declspec(property(get = getYear, put = setYear)) short Year;

	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool IsLeapYear()
	{
		IsLeapYear(Year);
	}

	static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Year, Month, Day, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (
			to_string(Year) + "/" + to_string(Month) + "/" + to_string(Day) +
			" - " +
			to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{

		if (Month < 0 || Month > 12)
			return 0;

		const short NumberOfDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];

	}
	short NumberOfDaysInMonth()
	{
		NumberOfDaysInMonth(Month, Year);
	}

	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		short a, y, m;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
	}

	short DayOfWeekOrder()
	{
		DayOfWeekOrder(Year, Month, Day);
	}

	static string DayShortName(short Year, short Month, short Day)
	{
		short dayOfWeekOrder = DayOfWeekOrder(Year, Month, Day);
		const string DaysShortNames[7] = { "Sun", "Mon", "Tue", "Wen", "Thi", "Fri", "Sat" };

		return DaysShortNames[dayOfWeekOrder];
	}
	string DayShortName()
	{
		return DayShortName(Year, Month, Day);
	}

	static string MonthShortName(short Month)
	{
		const string MonthShortNames[12] = { "Jan", "Feb", "March", "April","May", "Jun", "Jul","Aug", "Sep", "Oct", "Nov", "Dec" };
		return MonthShortNames[Month - 1];
	}
	string MonthShortName()
	{
		return MonthShortName(Month);
	}

	static bool isValidDate(clsDate Date)
	{
		if (Date.Day > 31 || Date.Day < 1 || Date.Month > 12 || Date.Month < 1 || Date.Year < 1)
			return false;

		else
			return (Date.Day <= clsDate::NumberOfDaysInMonth(Date.Month, Date.Year));
	}

	bool isValidDate()
	{
		return isValidDate(*this);
	}

	static void PrintMonthCalendar(short Year, short Month)
	{
		short NumberOfDays, dayOfWeekOrder;

		NumberOfDays = NumberOfDaysInMonth(Month, Year);
		dayOfWeekOrder = DayOfWeekOrder(Year, Month, 1);

		cout << "  \n  _______________" << MonthShortName(Month) << "_______________" << "\n\n";

		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";


		// Print spaces
		for (short i = 0; i < dayOfWeekOrder; i++)
		{
			printf("%*c", 5, ' ');
		}
		// Print Days Of Month 
		for (short i = 1; i <= NumberOfDays; i++)
		{
			printf("%*d", 5, i);
			if ((dayOfWeekOrder + i) % 7 == 0)
				cout << "\n";
		}
		cout << "\n  ---------------------------------\n";
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(Year, Month);
	}

	static void PrintYearCalender(short Year)
	{
		printf("\n  --------------------------------\n");
		printf("        Calendar - %d\n", Year);
		printf("  --------------------------------\n");

		for (short Month = 1; Month <= 12; Month++)
		{
			PrintMonthCalendar(Year, Month);
		}
	}
	void PrintYearCalender()
	{
		PrintYearCalender(Year);
	}

	static short TotalDaysFromBeginningOfYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}
	short TotalDaysFromBeginningOfYear()
	{
		return TotalDaysFromBeginningOfYear(Day, Month, Year);
	}

	static clsDate DateAddDays(clsDate& Date, short Days)
	{
		short RemainingDays = Days + TotalDaysFromBeginningOfYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;

		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Year++;
					Date.Month = 1;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;

	}
	void DateAddDays(short Days)
	{
		DateAddDays(*this, Days);
	}

	static bool IsDateBeforeDate(clsDate Date1, clsDate Date2)
	{

		return (Date1.Year < Date2.Year) ? true :
			((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true :
				(Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);

	}
	bool IsDateBeforeDate(clsDate Date2)
	{
		return IsDateBeforeDate(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{

		return (Date1.Year == Date2.Year ?
			(Date1.Month == Date2.Month ?
				(Date1.Day == Date2.Day) : false) : false);
	}
	bool IsDate1EqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year)) ? true : false;
	}
	bool IsLastDayInMonth()
	{
		IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}
		return Date;
	}
	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate.Day = Date1.Day;
		TempDate.Month = Date1.Month;
		TempDate.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;

		Date2.Day = TempDate.Day;
		Date2.Month = TempDate.Month;
		Date2.Year = TempDate.Year;

	}

	static int GetDiffDateInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDateBeforeDate(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDateBeforeDate(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	static int GetAgeInDays(clsDate& CurrentDate, clsDate Date1)
	{
		return GetDiffDateInDays(Date1, CurrentDate);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (IsDateBeforeDate(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				DaysCount++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DaysCount;
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short Days = VacationDays;

		for (short i = 1; i <= Days; i++)
		{
			if (IsWeekEnd(DateFrom))
				Days++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return DateFrom;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDateBeforeDate(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDateBeforeDate(Date1, Date2))
			return enDateCompare::Before;
		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDatesString = "";

		FormattedDatesString = clsString::ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		FormattedDatesString = clsString::ReplaceWordInString(FormattedDatesString, "mm", to_string(Date.Month));
		FormattedDatesString = clsString::ReplaceWordInString(FormattedDatesString, "yyyy", to_string(Date.Year));

		return FormattedDatesString;
	}
	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}

	void Print()
	{
		cout << Day << "/" << Month << "/" << Year << endl;
	}
};

