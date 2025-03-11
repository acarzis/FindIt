#include <gtest/gtest.h>
#include "../../Library/Utils/DriveOperations.h"

using namespace std;

TEST(DriveOperations, EnumerateFolders)
{
	list<string> folderlist;
	DriveOperations::EnumerateFolders("C:\\", folderlist);
	ASSERT_GE(folderlist.size(), 1);
}

TEST(DriveOperations, EnumerateFiles)
{
	list<string> filelist;
	DriveOperations::EnumerateFiles("C:\\Windows", filelist);
	ASSERT_GE(filelist.size(), 1);
}

TEST(DriveOperations, Filesize)
{
	long long filesize = DriveOperations::Filesize("C:\\Windows\\regedit.exe");
	ASSERT_GT(filesize, 0);
}
