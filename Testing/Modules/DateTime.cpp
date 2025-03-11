#include <gtest/gtest.h>
#include <string>
#include "../../Library/Utils/DateTime.h"

using namespace std;

TEST(DateTime, DateTestClass)
{
    std::time_t t = std::time(0);
    std::tm* now = std::gmtime(&t);
    string tnow = asctime(now);             //  Mon Feb 24 21:08:56 2025

    DateTime nowdt;
    string tnowdt = nowdt.AscTime();
    string tnowdt2 = nowdt.ToUTCString();   // passes visual inspection
    ASSERT_EQ(tnow, tnowdt);
}
