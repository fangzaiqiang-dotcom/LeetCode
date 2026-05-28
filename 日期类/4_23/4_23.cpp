#include<assert.h>

class Date
{

	Date(int year = 1900, int month = 1, int day = 1):_year(year),_month(month),_day(day){}
    Date(const Date&date)
		:_year(date._year)
		, _month (date._month)
		, _day(date._day)
	{
	}

public:
	int GetMonthDay(int year, int month)
	{
		assert(month > 0 && month < 13);
		static int MonthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && (year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			return 29;
		}
		else
		{
			return MonthDay[month];
		}
	}

	Date& operator=(const Date& d)
	{
		if (this == &d)
		{
			return *this;
		}
		else {
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
		}
	};


	Date operator+(int day)
	{
		Date tmp(*this);
		_day += day;
		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return tmp;
	};



	Date& operator+=(int day)
	{
		*this = *this + day;
		return *this;
	}
	
	
	Date operator-=(int day)
	{
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDay(_year, _month);
		}
		return *this;
	}

	Date& operator-(int day)
	{
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}

	Date& operator--()
	{
		*this = *this - 1;
		return *this;
	}
	Date& operator--(int)
	{
		Date tmp = *this;
		*this = *this - 1;
		return tmp;
	}
	Date& operator++()
	{
		*this = *this + 1;
		return *this;
	}
	Date& operator++(int)
	{
		Date tmp = *this;
		*this = *this + 1;
		return tmp;
	}


	bool operator>(const Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year ==d._year)
		{
			if(_month > d._month)
			return true;
		else if (_month == d._month)
			if(_day > d._day)
			return true;
		}
		else
			return false;
	}

	bool operator>=(const Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month > d._month)
				return true;
		else if (_month == d._month)
	     if (_day >= d._day)
				return true;
		}
		else
			return false;
	}
	bool operator<(const Date& d) 
	{
		if (_year < d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month < d._month)
				return true;
			else if (_month == d._month)
				if (_day < d._day)
					return true;
		}
		else
			return false;
	}
	bool operator<=(const Date& d)
	{
		if (_year < d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month < d._month)
				return true;
			else if (_month == d._month)
				if (_day <= d._day)
					return true;
		}
		else
			return false;
	}

	bool operator==(const Date& d)
	{
		return (_year==d._year&&_month==d._month&&_day==d._day);
	}
	bool operator!=(const Date& d)
	{
		return !(*this==d);
	}
	int operator-(const Date& d)
	{
		Date max = *this;
		Date min =d;
		int fuhao = 1;
		int day = 0;
		if (*this < d)
		{
			max = d;
			min = *this;
			fuhao = -1;
		}
		while (max > min)
		{
			min++;
			day++;
		}
		return day * fuhao;
	}

	void Print();
private:
	int _year;
	int _month;
	int _day;
};
