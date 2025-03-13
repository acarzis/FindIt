
#include "Folder.h"

using namespace std;

bool Folder::operator< (const Folder& right) const
{
	return _FullPathHash < right._FullPathHash;
}

Folder::Folder(): 
	_FolderSize(0)
{
}

Folder::Folder(string fullpathhash, string name, string path, string lastmodified, string lastchecked, int64_t foldersize, string category):
	_FullPathHash(fullpathhash), _Name(name), _Path(path), _LastModified(lastmodified), _LastChecked(lastchecked), 
	_FolderSize(foldersize), _CategoryName(category)
{
}

string Folder::GetFullPathHash() const
{
	return _FullPathHash;
}

string Folder::GetPathHash() const
{
	return _PathHash;
}

string Folder::GetName() const
{
	return _Name;
}

string Folder::GetPath() const
{
	return _Path;
}

int64_t Folder::GetFolderSize() const
{
	return _FolderSize;
}

DateTime Folder::GetLastChecked() const
{
	return _LastChecked;
}

DateTime Folder::GetLastModified() const
{
	return _LastModified;
}

string Folder::GetCategory() const
{
	return _CategoryName;
}


void Folder::SetFolderSize(int64_t foldersize)
{
	_FolderSize = foldersize;
}

void Folder::SetLastChecked(DateTime lastcheckedtime)
{
	_LastChecked = lastcheckedtime;
}

void Folder::SetCategoryName(string categoryname)
{
	_CategoryName = categoryname;
}

void Folder::SetLastModified(DateTime lastmodified)
{
	_LastModified = lastmodified;
}
