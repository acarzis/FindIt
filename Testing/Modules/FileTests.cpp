#include <gtest/gtest.h>
#include "../../Library/InMemoryDB/Files.h"
#include "../../Library/InMemoryDB/Folders.h"

TEST(FileTests, DoubleInsert)
{
	Files& files = Files::GetInstance();
	files.AddFile("D:\\Images30", "testfile31.txt", "", "", 0);
	files.AddFile("D:\\Images30", "testfile31.txt", "", "", 0);

	File f("D:\\Images30\\testfile31.txt", 0, "");
	string filename = Files::GetInstance().GetFileName(f.GetFullPathHash());

	ASSERT_EQ(filename, "testfile31.txt");
}
