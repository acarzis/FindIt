#pragma once

#include <set>
#include "../Entities/Folder.h"
#include "./Interfaces/IFolders.h"


using namespace std;

class Folders : public IFolders
{
	set<Folder> _folders;

public:
	static Folders& GetInstance();
	void Load();
	void WriteToDisk();
	int64_t GetCount();
	int64_t GetCount(string fullpath);
	virtual bool FolderExists(string folderpath, Folder& folder) override;
	virtual void AddFolder(string fullpath, string category, int64_t foldersize) override;
	void GetFolderDetails(string fullpath, string& category, int64_t& foldersize, DateTime& lastchecked, DateTime& lastmodified);
	void AddFolderDetails(string fullpath, string category, int64_t foldersize, DateTime& lastmodified, bool updateLastChecked = false);
	int64_t ComputeFolderSize(string fullpath);
	int64_t ComputeFolderSizeInternally(string fullpath);
	string GetFullPath(string folderhash);
};




/*
we want:  folder - count of files, count of folders

map <folderhash, file count/list>	-->		all files with that folder hash
map <folderhash, folder count/list>	-->		sub-folders with same parent folder hash

*/
