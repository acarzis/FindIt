#pragma once

#include <string> 
#include <chrono> 
#include <format> 

using namespace std;

class DateTime
{
	int _year = {};
	int _month = {};
	int _day = {};
	int _hour = {};
	int _min = {};
	int _sec = {};
	void Now();
	time_t GetTime_t() const;

public:
	DateTime();
	DateTime(time_t);
	DateTime(string datetimestring);
	string ToUTCString() const;
	string AscTime() const;
	bool operator> (const DateTime& right) const;
	bool operator>= (const DateTime& right) const;
};
