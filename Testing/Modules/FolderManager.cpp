#include <gtest/gtest.h>
#include "../../Library/InMemoryDB/FolderManager.h"
#include "../../Library/InMemoryDB/Folders.h"
#include "../../Library/InMemoryDB/Files.h"



TEST(FolderManager, GeneralTests)
{
	FolderManager &fm = FolderManager::GetInstance();

	fm.AddFile("c:\\Windows", "angelo.txt");
	fm.AddFile("c:\\Windows", "angelo2.txt");
	fm.AddChildFolder("c:\\Windows", "Boot");
	fm.AddChildFolder("c:\\Windows", "Tasks");
	fm.AddChildFolder("c:\\Windows", "Temp");

	ASSERT_EQ(2, fm.GetFileCount("c:\\Windows"));
	ASSERT_EQ(3, fm.GetFolderCount("c:\\Windows"));
}


TEST(FolderManager, EnumerateFolders)
{
	FolderManager& fm = FolderManager::GetInstance();
	Folders& f = Folders::GetInstance();
	f.AddFolder("D:\\Images20\\child1", "", 0);
	f.AddFolder("D:\\Images21\\child2", "", 0);
	f.AddFolder("D:\\Images22\\child3", "", 0);
	f.AddFolder("D:\\Images22\\child4", "", 0);
	fm.AddChildFolder("D:\\Images20", "child1");
	fm.AddChildFolder("D:\\Images21", "child2");
	fm.AddChildFolder("D:\\Images22", "child3");
	fm.AddChildFolder("D:\\Images22", "child4");

	Files& files = Files::GetInstance();
	files.AddFile("D:\\Images20", "testfile1.txt", "", "", 0);		// calls FolderManager::AddFile()
	files.AddFile("D:\\Images20", "testfile2.txt", "", "", 0);
	files.AddFile("D:\\Images21", "testfile3.txt", "", "", 0);
	files.AddFile("D:\\Images21", "testfile4.txt", "", "", 0);
	files.AddFile("D:\\Images21", "testfile5.txt", "", "", 0);
	files.AddFile("D:\\Images22", "testfile6.txt", "", "", 0);
	files.AddFile("D:\\Images22", "testfile7.txt", "", "", 0);
	files.AddFile("D:\\Images22", "testfile8.txt", "", "", 0);
	files.AddFile("D:\\Images22", "testfile9.txt", "", "", 0);

	list<string> folderlist;
	fm.EnumerateFolders("D:\\Images20", folderlist);
	ASSERT_EQ(1, folderlist.size());

	folderlist.clear();
	fm.EnumerateFolders("D:\\Images22", folderlist);
	ASSERT_EQ(2, folderlist.size());

	list<string> fileslist;
	fm.EnumerateFiles("D:\\Images20", fileslist);
	ASSERT_EQ(2, fileslist.size());

	fileslist.clear();
	fm.EnumerateFiles("D:\\Images21", fileslist);
	ASSERT_EQ(3, fileslist.size());

}

TEST(FolderManager, EnumerateFiles)
{
}
