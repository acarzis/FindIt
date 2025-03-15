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
	fs::path absolutePath = fs::path(folderfullpath) / fs::path(filename);
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
	fs::path absolutePath = fs::path(folderfullpath) / fs::path(subfoldername);
	string subfolderhash = SHA256HashString(absolutePath.string());

	auto it = _folderlist.find(hash);
	if (it != _folderlist.end())
	{
		list<string> temp = _folderlist[hash];
		if (std::find(temp.begin(), temp.end(), subfolderhash) == temp.end())
		{
			temp.push_back(subfolderhash);
			_folderlist[hash] = temp;
		}
	}
	else
	{
		list<string> temp;
		temp.push_back(subfolderhash);
		_folderlist[hash] = temp;
	}
}


void FolderManager::EnumerateFolders(string fullpath, list<string>& folderlistfullpath)
{
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

			fs::path absolutePath = fs::path(fullpath) / fs::path(subfoldername) ;
			folderlistfullpath.push_back(absolutePath.string());			// subfoldername);
		}
	}
}

void FolderManager::EnumerateFiles(string fullpath, list<string>& filelistfullpath)
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

			fs::path absolutePath = fs::path(fullpath) / fs::path(filename);
			filelistfullpath.push_back(absolutePath.string());						// filename);
		}
	}
}

int64_t FolderManager::ComputeParentFolderSize(string fullpath)
{
	int64_t size = 0;
	fs::path folder(fullpath);
	string parentpath = folder.parent_path().string();

	string hash = SHA256HashString(parentpath);
	auto it = _folderlist.find(hash);
	if (it != _folderlist.end())
	{
		list<string> subfolders = it->second;
		for (string subfoldernamehash : subfolders)
		{
			string subfoldername = Folders::GetInstance().GetFullPath(subfoldernamehash);
			Folder foldertemp;
			Folders::GetInstance().FolderExists(subfoldername, foldertemp);
			size += foldertemp.GetFolderSize();
		}

		auto it2 = _filelist.find(hash);
		if (it2 != _filelist.end())
		{
			list<string> files = it2->second;
			for (string filefullpathhash : files)
			{
				fs::path parentfolder(parentpath);
				fs::path absolutePath = parentfolder / Files::GetInstance().GetFileName(filefullpathhash);

				File temp(absolutePath.string(), 0, "");
				Files::GetInstance().GetFile(absolutePath.string(), temp);
				size += temp.GetFilesize();
			}
		}
	}
	return size;
}

void FolderManager::PopulateFolderData(set<Folder> &folderset)
{
	for (Folder folder : folderset)
	{
		fs::path path(folder.GetPath());
		fs::path name(folder.GetName());

		if (!name.string().empty())
		{
			FolderManager::AddChildFolder(path.string(), name.string());
		}
	}
}

void FolderManager::PopulateFileData(set<File> &fileset)
{
	for (File file : fileset)
	{
		string folderfullpath = Folders::GetInstance().GetFullPath(file.GetFolderHash());
		FolderManager::AddFile(folderfullpath, file.GetName());
	}
}
