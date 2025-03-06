#pragma once

#include <list>
#include <string>
#include "DateTime.h"

using namespace std;


class DriveOperations
{
public:
	DriveOperations() = delete;
	static void EnumerateFolders(string fullpath, list<string>& folderlist);
	static void EnumerateFiles(string fullpath, list<string>& filelist);
	static uintmax_t Filesize(string fullpath);
	static DateTime GetLastWriteTime(string foldername);
};

