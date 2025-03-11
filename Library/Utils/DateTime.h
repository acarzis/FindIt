#pragma once

#include <string> 
#include <chrono> 
#include <format> 

// date libraries:
// https://github.com/HowardHinnant/date


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
	DateTime(std::string datetimestring);
	std::string ToUTCString() const;
	std::string AscTime() const;
	bool operator> (const DateTime& right) const;
	bool operator>= (const DateTime& right) const;
};
