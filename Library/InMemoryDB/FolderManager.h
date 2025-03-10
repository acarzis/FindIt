#pragma once

#include <list>
#include <map>
#include <string>

/*
we want : folder - count of files, count of folders

map <folderhash, file count / list>	-- > all files with that folder hash
map <folderhash, folder count / list>	-- > sub - folders with same parent folder hash
*/


using namespace std;

class FolderManager
{
private:
	map<string, list<string>> _filelist;					// folderfullpath hash - filenamehash  hash --> filefullpath hash
	map<string, list<string>> _folderlist;					// folderfullpath hash - subfoldername hash --> subfolder fullpath hash 


public:
	static FolderManager& GetInstance();
	int64_t GetFolderCount(string folderfullpath);
	int64_t GetFileCount(string folderfullpath);

	void AddFile(string folderfullpath, string filename);
	void AddChildFolder(string folderfullpath, string subfoldername);
	void EnumerateFolders(string fullpath, list<string>& folderlistfullpath);
	void EnumerateFiles(string fullpath, list<string>& filelistfullpath);
	int64_t ComputeParentFolderSize(string fullpath);
};
