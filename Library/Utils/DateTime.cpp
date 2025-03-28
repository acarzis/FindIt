
#include <string>
#include <chrono>
#include <ctime>
#include "DateTime.h"


using namespace std;


// future rteference:
//    https://www.cppstories.com/2024/chrono_dates_zones/#:~:text=In%20this%20blog%20post%2C%20we%20will%20explore%20handling,into%20account%20daylight%20saving%20time%20changes%20as%20well.


/*
        mktime converts tm structure into time, i.e. the reverse of localtime
        _mkgmtime converts tm structure into a UTC time, gmtime converts a gmt time into a tm structure
        ctime       - for representing UTC times as a string    format: Sun Sept 16 01:03:52 1973\n\0
        asctime     - for representing local times as a string
*/

void DateTime::Now()
{
    /*
    std::chrono::local_time<std::chrono::system_clock::duration> const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
    std::chrono::system_clock::duration d = time.time_since_epoch();
    std::chrono::system_clock::time_point tp(d);
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(tp);  
    */

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();        // in UTC
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(tp);
    std::tm *tm = gmtime(&now_time_t);          // convert time since epoch to UTC time, tm->tm_isdst always 0 for gmtime()
    _year = tm->tm_year;                        // current year - 1900
    _month = tm->tm_mon;
    _day = tm->tm_mday;
    _hour = tm->tm_hour;
    _min = tm->tm_min;
    _sec = tm->tm_sec;
}

DateTime::DateTime(string datetimestring)
{
    // Format:  2025-03-11 12:57:20 - in UTC

    if (datetimestring.empty())
    {
        DateTime now;
        datetimestring = now.ToUTCString();
    }

    _year = stoi(datetimestring.substr(0, 4)) - 1900;
    _month = stoi(datetimestring.substr(5, 2)) - 1;
    _day = stoi(datetimestring.substr(8, 2));
    _hour = stoi(datetimestring.substr(11, 2));
    _min = stoi(datetimestring.substr(14, 2));
    _sec = stoi(datetimestring.substr(17, 2));
}

DateTime::DateTime()
{
    Now();
}

DateTime::DateTime(time_t time)
{
    std::tm* tm = gmtime(&time);    // convert time since epoch to UTC time
    _year = tm->tm_year;
    _month = tm->tm_mon;
    _day = tm->tm_mday;
    _hour = tm->tm_hour;
    _min = tm->tm_min;
    _sec = tm->tm_sec;
}

string DateTime::ToUTCString() const
{
    string res;

    std::tm tm{};
    tm.tm_year = _year;
    tm.tm_mon = _month;
    tm.tm_mday = _day;
    tm.tm_hour = _hour;
    tm.tm_min = _min;
    tm.tm_sec = _sec;
    std::time_t thetime = _mkgmtime(&tm);     // converts local time to time_t 
    char result[100];

    if (strftime(result, sizeof(result), "%Y-%m-%d %X", std::gmtime(&thetime)))
    {
        res = string(result);
    }
    return res;
}

string DateTime::AscTime() const
{
    string res;

    std::tm utc{};
    utc.tm_year = _year;
    utc.tm_mon = _month;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = _mkgmtime(&utc);
    return asctime(&utc);
}

time_t DateTime::GetTime_t() const
{
    struct tm utc;
    utc.tm_year = _year;
    utc.tm_mon = _month;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = _mkgmtime(&utc);
    return thetime;
}

bool DateTime::operator> (const DateTime& right) const
{
    struct tm utc;
    utc.tm_year = _year;
    utc.tm_mon = _month;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = _mkgmtime(&utc);

    std::time_t righttime_t  = right.GetTime_t();

    if (thetime > righttime_t)
        return true;

    return false;
};

bool DateTime::operator>= (const DateTime& right) const
{
    struct tm utc;
    utc.tm_year = _year;
    utc.tm_mon = _month;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = _mkgmtime(&utc);

    std::time_t righttime_t = right.GetTime_t();

    if (thetime >= righttime_t)
        return true;

    return false;
};

