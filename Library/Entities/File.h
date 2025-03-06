#pragma once

#include <string>
#include "Folder.h"

using namespace std;

class File
{
	string _FullPathHash;
	string _Name;
	int64_t _FileSize;
	string _FolderHash;
	string _CategoryName;

	// foreign keys
	//Folder &Folder;
	//Category &Category;

public:
	File(string fullpath, int64_t filesize, string categoryname);
	File(string fullpathhash);						// TO DO: only useful for searching. Try to do better
	bool operator< (const File& right) const;
	int64_t GetFilesize() const;
	string GetName() const;
	string GetFullPathHash() const;
	string GetFolderHash() const;
};
