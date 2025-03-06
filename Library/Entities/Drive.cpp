
#include "Drive.h"

Drive::Drive(string logicalname, string name, int scanpriority) :
    _LogicalDrive(logicalname), _Name(name), _ScanPriority(scanpriority)
{
};

string Drive::GetName()
{
    return _Name;
}

string Drive::GetLogicalDriveName()
{
    return _LogicalDrive;
}
