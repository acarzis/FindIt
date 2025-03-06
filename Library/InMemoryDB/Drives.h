#pragma once

#include <list>
#include <string>
#include "../Entities/Drive.h"
#include "./Interfaces/IDrives.h"


using namespace std;

class Drives : IDrives
{
    list<Drive> _drives;

public:
    static Drives& GetInstance();
    void Load();
    virtual void GetDriveList(list<Drive>& drives) override;
    virtual void AddDrive(string drive, string name, int priority = 0) override;
};
