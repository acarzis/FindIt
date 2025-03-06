#pragma once

#include <string>
#include <list>
#include "../../Entities/Drive.h"

using namespace std;

class IDrives
{
    virtual void GetDriveList(list<Drive> &drives) = 0;
    virtual void AddDrive(string drive, string name, int priority = 0) = 0;
};

