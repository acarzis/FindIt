#pragma once

#include <string>

using namespace std;

class Drive
{
    string _LogicalDrive;
    string _Name;
    int _ScanPriority;

public:
    Drive(string logicalname, string name, int scanpriority);
    string GetName();
    string GetLogicalDriveName();
};
