#include <gtest/gtest.h>
#include <string>
#include "../../Library/InMemoryDB/Folders.h"


TEST(FolderTests, FolderExists)
{
    string fullpath = "D:\\Images";
    Folders& f = Folders::GetInstance();
    long int before = f.GetCount();
    f.AddFolder(fullpath, "", 0);
    Folder tempfolder;
    long int after = f.GetCount();
    ASSERT_EQ(1, after - before);

    bool exists = false;
    if (f.FolderExists(fullpath, tempfolder))
    {
        exists = true;
    }

    f.AddFolder(fullpath, "", 0);
    long int after2 = f.GetCount();
    ASSERT_EQ(0, after2 - after);

    ASSERT_EQ(exists, true);
    ASSERT_EQ(tempfolder.GetName(), "Images");
    ASSERT_EQ(tempfolder.GetPath(), "D:\\");
}


TEST(FolderTests, GetFolderNameFromHash)
{
    string fullpath = "D:\\Images";
    Folders& f = Folders::GetInstance();
    f.AddFolder(fullpath, "", 0);

    Folder tempfolder;
    bool exists = false;
    if (f.FolderExists(fullpath, tempfolder))
    {
        exists = true;
    }
    ASSERT_EQ(exists, true);

    string fullname = f.GetFullPath(tempfolder.GetFullPathHash());
    ASSERT_EQ(fullname, "D:\\Images");
    ASSERT_EQ(tempfolder.GetName(), "Images");
    ASSERT_EQ(tempfolder.GetPath(), "D:\\");
}
