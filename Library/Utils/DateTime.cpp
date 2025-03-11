
#include <string>
#include <chrono>
#include <ctime>
#include "DateTime.h"


using namespace std;


// future rteference:
//    https://www.cppstories.com/2024/chrono_dates_zones/#:~:text=In%20this%20blog%20post%2C%20we%20will%20explore%20handling,into%20account%20daylight%20saving%20time%20changes%20as%20well.

void DateTime::Now()
{
    // auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());    
    std::chrono::local_time<std::chrono::system_clock::duration> const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());

    std::chrono::system_clock::duration d = time.time_since_epoch();
    std::chrono::system_clock::time_point tp(d);
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(tp);  
    std::tm *tm = gmtime(&now_time_t);          // convert time since epoch to UTC time, tm->tm_isdst always 0 for gmtime()
    _year = tm->tm_year;                        // current year - 1900
    _month = tm->tm_mon+1;
    _day = tm->tm_mday;
    _hour = tm->tm_hour;
    _min = tm->tm_min;
    _sec = tm->tm_sec;
}

DateTime::DateTime(string datetimestring)
{
    // TO DO - parse datetime db object
}

DateTime::DateTime()
{
    Now();
}

DateTime::DateTime(time_t time)
{
    std::tm* tm = gmtime(&time);    // convert time since epoch to UTC time
    _year = tm->tm_year;
    _month = tm->tm_mon + 1;
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
    tm.tm_mon = _month - 1;
    tm.tm_mday = _day;
    tm.tm_hour = _hour;
    tm.tm_min = _min;
    tm.tm_sec = _sec;
    tm.tm_isdst = -1;
    std::time_t thetime = std::mktime(&tm);
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

    std::tm tm{};
    tm.tm_year = _year;
    tm.tm_mon = _month - 1;
    tm.tm_mday = _day;
    tm.tm_hour = _hour;
    tm.tm_min = _min;
    tm.tm_sec = _sec;
    tm.tm_isdst = -1;
    std::time_t thetime = std::mktime(&tm);
    return asctime(std::gmtime(&thetime));
}

time_t DateTime::GetTime_t() const
{
    struct tm utc;
    utc.tm_year = _year;
    utc.tm_mon = _month - 1;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = mktime(&utc);
    return thetime;
}

bool DateTime::operator> (const DateTime& right) const
{
    struct tm utc;
    utc.tm_year = _year;
    utc.tm_mon = _month - 1;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = mktime(&utc);

    std::time_t righttime_t  = right.GetTime_t();

    if (thetime > righttime_t)
        return true;

    return false;
};

bool DateTime::operator>= (const DateTime& right) const
{
    struct tm utc;
    utc.tm_year = _year;
    utc.tm_mon = _month - 1;
    utc.tm_mday = _day;
    utc.tm_hour = _hour;
    utc.tm_min = _min;
    utc.tm_sec = _sec;
    utc.tm_isdst = -1;
    std::time_t thetime = mktime(&utc);

    std::time_t righttime_t = right.GetTime_t();

    if (thetime >= righttime_t)
        return true;

    return false;
};

