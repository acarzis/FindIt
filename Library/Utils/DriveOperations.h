#pragma once

#include <list>
#include <string>
#include "DateTime.h"


class DriveOperations
{
public:
	DriveOperations() = delete;
	static void EnumerateFolders(std::string fullpath, std::list<std::string>& folderlist);
	static void EnumerateFiles(std::string fullpath, std::list<std::string>& filelist);
	static uintmax_t Filesize(std::string fullpath);
	static DateTime GetLastWriteTime(std::string foldername);
	static void PrintDriveDetails(std::wstring drive);
	static std::vector<std::string> getListOfDrives();
	static std::wstring UNCPathW(std::string path);
	static std::string UNCPath(std::string path);
};

