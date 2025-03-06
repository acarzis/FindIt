#include "Folders.h"
#include <boost/filesystem.hpp>
#include "../Db/Operations.h"
#include "../Entities/Folder.h"
#include "../Entities/File.h"
#include "../Utils/DriveOperations.h"
#include "../Utils/Encryption.h"
#include "Files.h"
#include "FolderManager.h"

extern std::string DBNAME;

namespace fs = boost::filesystem;

bool Folders::FolderExists(string folderpath, Folder& folder)
{
	Folder temp(SHA256HashString(folderpath), "", "", "", "", 0);
	std::set<Folder>::const_iterator it = _folders.find(temp);
	if (it != _folders.end())
	{
		folder = *it;
		return true;
	}
	return false;
}

Folders& Folders::GetInstance()
{
	static Folders _instance;
	return _instance;
}

void Folders::Load()
{
	Operations op(::DBNAME);
	op.LoadFolders(_folders);
}


void Folders::AddFolder(string fullpath, string category, int64_t foldersize)
{
	// TO DO - add category
	std::string name = fs::path(fullpath).filename().string();
	std::string path = fs::path(fullpath).parent_path().string();

	DateTime now;
	Folder temp(SHA256HashString(fullpath), name, path, now.ToUTCString(), now.ToUTCString(), foldersize);
	std::set<Folder>::const_iterator it = _folders.find(temp);
	if (it == _folders.end())
	{
		_folders.insert(temp);
	}
}

int64_t Folders::GetCount()
{
	return _folders.size();
}

int64_t Folders::GetCount(string fullpath)
{
	return FolderManager::GetInstance().GetFolderCount(fullpath);
}

void Folders::GetFolderDetails(string fullpath, string &category, int64_t &foldersize, DateTime &lastchecked, DateTime &lastmodified)
{
	std::string name = fs::path(fullpath).filename().string();
	std::string path = fs::path(fullpath).parent_path().string();

	DateTime now;
	Folder temp(SHA256HashString(fullpath), name, path, now.ToUTCString(), now.ToUTCString(), foldersize);
	std::set<Folder>::const_iterator it = _folders.find(temp);
	foldersize = 0;
	category = "";
	if (it != _folders.end())
	{
		category = it->GetCategory();
		foldersize = it->GetFolderSize();
		lastchecked = it->GetLastChecked();
		lastmodified = it->GetLastModified();
	}
}

void Folders::AddFolderDetails(string fullpath, string category, int64_t foldersize, DateTime& lastmodified, bool updateLastChecked)
{
	std::string name = fs::path(fullpath).filename().string();
	std::string path = fs::path(fullpath).parent_path().string();

	DateTime now;
	Folder temp(SHA256HashString(fullpath), name, path, lastmodified.ToUTCString(), now.ToUTCString(), foldersize);
	std::set<Folder>::const_iterator it = _folders.find(temp);
	if (it != _folders.end())
	{
		temp = *it;
		temp.SetLastModified(lastmodified);

		if (foldersize != 0) {
			temp.SetFolderSize(foldersize);
		}

		if (updateLastChecked) {
			temp.SetLastChecked(now);
		}

		if (!category.empty()) {
			temp.SetCategoryName(category);
		}

		_folders.erase(it);
		_folders.insert(temp);
	}
}

int64_t Folders::ComputeFolderSize(string fullpath)
{
	// Performed recursively, accesses file system if need be
	int64_t result = 0;
	DateTime now;
	Folder foldertemp(SHA256HashString(fullpath), "", "", "", "", 0);

	list<string> folderlist;
	DriveOperations::EnumerateFolders(fullpath, folderlist);
	for (string folder : folderlist)
	{
		string category;
		int64_t foldersize;
		DateTime lastchecked, lastmodified;

		result += ComputeFolderSize(folder);
	};

	// compute file sizes
	list<string> filelist;
	DriveOperations::EnumerateFiles(fullpath, filelist);
	for (string file : filelist)
	{
		File temp(file, 0, "");
		try
		{
			Files::GetInstance().GetFile(file, temp);
			result += temp.GetFilesize();
		}
		catch (exception) 
		{
			fs::path path(file);
			uintmax_t size = DriveOperations::Filesize(file);
			Files::GetInstance().AddFile(path.parent_path().string(), path.filename().string(), "", "", size);	// TO DO: add folder category, file category 
			result += size;
		}
	}

	// TO DO: add support for category
	std::set<Folder>::const_iterator it = _folders.find(foldertemp);
	if (it != _folders.end())
	{
		DateTime lastmodified = (*it).GetLastModified();
		AddFolderDetails(fullpath, "", result, lastmodified, false);
	}
	else
	{
		DateTime lastmodified;
		AddFolderDetails(fullpath, "", result, lastmodified, false);
	}

	return result;
}


// WORK IN PROGRESS
int64_t Folders::ComputeFolderSizeInternally(string fullpath)
{
	// Performed recursively - Does not enumerate file system
	int64_t result = 0;
	DateTime now;
	Folder foldertemp(SHA256HashString(fullpath), "", "", "", "", 0);

	list<string> folderlist;
	
	try 
	{
		FolderManager::GetInstance().EnumerateFolders(fullpath, folderlist);
	}
	catch (exception &e)  {}

	for (string folder : folderlist)
	{
		string category;
		int64_t foldersize;
		DateTime lastchecked, lastmodified;

		result += ComputeFolderSizeInternally(folder);
	};

	// compute file sizes
	list<string> filelist;

	try 
	{
		FolderManager::GetInstance().EnumerateFiles(fullpath, filelist);
	}
	catch (exception& e) {}

	for (string file : filelist)
	{
		File temp(file, 0, "");
		try
		{
			Files::GetInstance().GetFile(file, temp);
			result += temp.GetFilesize();
		}
		catch (exception)
		{
			fs::path path(file);
			uintmax_t size = DriveOperations::Filesize(file);
			Files::GetInstance().AddFile(path.parent_path().string(), path.filename().string(), "", "", size);	// TO DO: add folder category, file category 
			result += size;
		}
	}

	// TO DO: add support for category
	std::set<Folder>::const_iterator it = _folders.find(foldertemp);
	if (it != _folders.end())
	{
		DateTime lastmodified = (*it).GetLastModified();
		AddFolderDetails(fullpath, "", result, lastmodified, false);
	}
	else
	{
		DateTime lastmodified;
		AddFolderDetails(fullpath, "", result, lastmodified, false);
	}

	return result;
}

string Folders::GetFullPath(string folderhash)
{
	string result;
	Folder foldertemp(folderhash, "", "", "", "", 0);
	std::set<Folder>::const_iterator it = _folders.find(foldertemp);
	if (it != _folders.end())
	{
		fs::path absolutePath = boost::filesystem::absolute(fs::path(it->GetName()), fs::path(it->GetPath()));
		result = absolutePath.string();
	}
	else
	{
		throw runtime_error("Folder not found");
	}
	return result;
}
