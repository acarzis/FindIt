

// for Folder processing
/*
bool AddFolder(string folderpath, string category, long foldersize);
bool AddFolderDetails(string folderpath, string category, long foldersize, DateTime lastmodified, bool updateLastChecked);
long GetFolderSize(string folderpath);
string GetFolderCategory(string folderpath);
bool GetFolderDetails(string folderpath, out Category cat, out long foldersize, out DateTime lastchecked, out DateTime lastmodified);
bool GetAllFolders(out IEnumerable<Folder> folders, string namesearchpattern = "", string pathsearchpattern = "");
bool FolderExists(string folderpath, out Folder folder);
*/

#include <string> 
#include "../../Entities/Folder.h"

using namespace std;

class IFolders
{
	virtual bool FolderExists(string folderpath, Folder &folder) = 0;
	virtual void AddFolder(string fullpath, string category, int64_t foldersize) = 0;
};
