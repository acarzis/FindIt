#include "Drives.h"

#include <list>
#include "../Db/Operations.h"

using namespace std;

extern std::string DBNAME;

void Drives::Load()
{
	Operations op(::DBNAME);
	op.LoadDrives(_drives);
}

Drives& Drives::GetInstance()
{
	static Drives _instance;
	return _instance;
}

void Drives::GetDriveList(list<Drive>& drives)
{
	drives = _drives;
}

void Drives::AddDrive(string drive, string name, int priority)
{
	Drive d(drive, name, priority);
	_drives.push_back(d);
}
