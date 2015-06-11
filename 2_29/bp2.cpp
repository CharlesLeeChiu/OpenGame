#include <iostream>
#include <string>
#include <map>
using namespace std;
struct Date{
	int _year;
	int _month;
	int _day;
	Date(int y, int m,int d) :_year(y), _month(m), _day(d){}
	Date()	{}
	bool operator <(const Date &a);
	bool operator ==(const Date &a);
	bool operator <=(const Date &a);
	Date operator -(const Date &a);
	Date operator +(const Date &a);
	Date operator =(const Date &a);
	Date& operator++(int);
};
Date inline yearToDate(int y);
bool IsBissextile(int y);
map<string,int> MonthToInt;
int solve(Date &s, Date &e);
void Init();
inline bool Date::operator<(const Date &a)
{
	if (this->_year < a._year){
		return true;
	}
	else if (this->_year > a._year){
		return false;
	}
	else
	{
		if (this->_month < a._month){
			return true;
		}
		else if (this->_month > a._month){
			return false;
		}
		else
		{
			if (this->_day < a._day){
				return true;
			}
			else{
				return false;
			}
		}
	}

}
inline bool Date::operator==(const Date &a)
{
	if (this->_year == a._year&&
		this->_month == a._month&&
		this->_day == a._day){
		return true;
	}
	else{
		return false;
	}
}
inline bool Date::operator<=(const Date &a)
{
	return operator<(a) || operator==(a);
}
inline Date Date::operator=(const Date &a)
{
	this->_year = a._year;
	this->_month = a._month;
	this->_day = a._day;
	return *this;
}
inline Date Date::operator+(const Date &a)
{
	int y = this->_year + a._year;
	int m = this->_month + a._month;
	int d = this->_day + a._day;
	return Date(y, m, d);
}
inline Date Date::operator-(const Date &a)
{
	int y = this->_year - a._year;
	int m = this->_month - a._month;
	int d = this->_day - a._day;
	return Date(y, m, d);
}
inline Date& Date::operator++(int)
{
	this->_year += 4;
	while (!IsBissextile(this->_year))
	{
		this->_year += 4;
	}
	return *this;
}
int main(int argc, char* argv[])
{
	Init();
	int t;
	cin >> t;
	string mm = "";
	int y, m, d;
	for (int i = 1; i <= t; i++)
	{
		string tmp;
		cin >> mm >> d >> tmp >> y;
		m = MonthToInt[mm];
		Date start(y, m, d);
		cin >> mm >> d >> tmp >> y;
		m = MonthToInt[mm];
		Date end(y, m, d);
		int ret = solve(start, end);
		cout << "Case #" << i << ": " << ret << endl;
	}
	return 0;
}
void Init()
{
	/**/
	MonthToInt["January"] = 1;
	MonthToInt["February"] = 2;
	MonthToInt["March"] = 3;
	MonthToInt["April"] = 4;
	MonthToInt["May"] = 5;
	MonthToInt["June"] = 6;
	MonthToInt["July"] = 7;
	MonthToInt["August"] = 8;
	MonthToInt["September"] = 9;
	MonthToInt["October"] = 10;
	MonthToInt["November"] = 11;
	MonthToInt["December"] = 12;
}
int solve(Date &s, Date &e)
{
	//
	int res = 0;
	Date s_new;
	if (IsBissextile(s._year))
	{
		s_new = yearToDate(s._year);
	}
	else
	{
		int tmp_y = s._year + (4 - s._year % 4);
		while (!IsBissextile(tmp_y))
		{
			tmp_y += 4;
		}
		s_new = yearToDate(tmp_y);
	}
	if ((s <= s_new)&&(s_new <= e))
	{
		res = 1;
	}
	else
	{
		res = 0;
	}
	s_new++;
	while (s_new <= e)
	{
		res++;
		s_new++;
	}	
	return res;
}
Date inline yearToDate(int y)
{
	return Date(y, 2, 29);
}
bool IsBissextile(int y)
{
	if (y % 400 == 0)
	{
		return true;
	}
	else
	{
		if (y % 100 != 0 && y % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}