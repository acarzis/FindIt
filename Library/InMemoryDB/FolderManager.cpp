#include <boost/filesystem.hpp>
#include "FolderManager.h"
#include "../Utils/Encryption.h"
#include "Folders.h"
#include "Files.h"

namespace fs = boost::filesystem;

FolderManager& FolderManager::GetInstance()
{
	static FolderManager _instance;
	return _instance;
}

int64_t FolderManager::GetFolderCount(string folderfullpath)
{
	int64_t count = 0;
	string hash = SHA256HashString(folderfullpath);
	auto it = _folderlist.find(hash);
	if (it != _folderlist.end())
	{
		list<string> temp = _folderlist[hash];
		count = temp.size();
	}
	return count;
}

int64_t FolderManager::GetFileCount(string folderfullpath)
{
	int64_t count = 0;
	string hash = SHA256HashString(folderfullpath);
	auto it = _filelist.find(hash);
	if (it != _filelist.end())
	{
		list<string> temp = _filelist[hash];
		count = temp.size();
	}
	return count;
}

void FolderManager::AddFile(string folderfullpath, string filename)
{
	// ** TO DO ***: Improve this.Don't allow duplicate file entries.

	string hash = SHA256HashString(folderfullpath);
	fs::path absolutePath = boost::filesystem::absolute(fs::path(filename), fs::path(folderfullpath));
	string filehash = SHA256HashString(absolutePath.string());

	auto it = _filelist.find(hash);
	if (it != _filelist.end())
	{
		list<string> temp = _filelist[hash];
		temp.push_back(filehash);
		_filelist[hash] = temp;
	}
	else
	{
		list<string> temp;
		temp.push_back(filehash);
		_filelist[hash] = temp;
	}
}

void FolderManager::AddChildFolder(string folderfullpath, string subfoldername)
{
	string hash = SHA256HashString(folderfullpath);
	fs::path absolutePath = boost::filesystem::absolute(fs::path(subfoldername), fs::path(folderfullpath));
	string subfolderhash = SHA256HashString(absolutePath.string());

	auto it = _folderlist.find(hash);
	if (it != _folderlist.end())
	{
		list<string> temp = _folderlist[hash];
		temp.push_back(subfolderhash);
		_folderlist[hash] = temp;
	}
	else
	{
		list<string> temp;
		temp.push_back(subfolderhash);
		_folderlist[hash] = temp;
	}
}


void FolderManager::EnumerateFolders(string fullpath, list<string>& folderlist)
{
	// TO DO:   folderlist must have full path of each folder

	string hash = SHA256HashString(fullpath);
	auto it = _folderlist.find(hash);

	// Files are stored as:  folderfullpath hash - subfolder fullpath hash
	if (it != _folderlist.end())
	{
		list<string> subfolders = it->second;
		for (string subfoldernamehash : subfolders)
		{
			// get subfolder name from sub-foldername hash
			string subfoldername = Folders::GetInstance().GetFullPath(subfoldernamehash);
			// fs::path sfname(subfoldername);
			// subfoldername = sfname.filename().string();

			fs::path absolutePath = boost::filesystem::absolute(fs::path(subfoldername), fs::path(fullpath));
			folderlist.push_back(absolutePath.string());			// subfoldername);
		}
	}
}

void FolderManager::EnumerateFiles(string fullpath, list<string>& filelist)
{
	// TO DO:   filelist must have full path of each folder

	string hash = SHA256HashString(fullpath);
	auto it = _filelist.find(hash);

	if (it != _filelist.end())							// folderfullpath hash - filefullpath hash
	{
		list<string> files = it->second;
		for (string fullpathhash : files)
		{
			string filename = Files::GetInstance().GetFileName(fullpathhash);

			fs::path absolutePath = boost::filesystem::absolute(fs::path(filename), fs::path(fullpath));
			filelist.push_back(absolutePath.string());						// filename);
		}
	}
}
