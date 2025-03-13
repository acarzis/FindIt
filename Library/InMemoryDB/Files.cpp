#include "Files.h"
#include <boost/filesystem.hpp>
#include "../Utils/Encryption.h"
#include "Folders.h"
#include "FolderManager.h"
#include "../Db/Operations.h"

using namespace std;
namespace fs = boost::filesystem;

extern std::string DBNAME;

void Files::AddFile(string dirname, string fname, string foldercategory, string filecategory, int64_t filesize)
{
	fs::path absolutePath = boost::filesystem::absolute(fs::path(fname), fs::path(dirname));
	string fullpath = absolutePath.string();

	File f(fullpath, filesize, filecategory);
	if (_files.insert(f).second == true)
	{
		FolderManager::GetInstance().AddFile(dirname, fname);
		Folders::GetInstance().AddFolder(dirname, foldercategory, 0);
	}
}

void Files::AddFileDetails(string filepath, string category, int64_t filesize)
{
	// TO DO
}

set<File>& Files::GetAllFiles()
{
	return _files;
}

Files& Files::GetInstance()
{
	static Files _instance;
	return _instance;
}

int64_t Files::GetCount()
{
	return _files.size();
}

void Files::GetFile(string filepath, File& file)
{
	File temp(filepath, 0, "");
	std::set<File>::const_iterator it = _files.find(temp);
	if (it != _files.end())
	{
		file = *it;
	}
	else
	{
		throw runtime_error("File not found - filepath: " + filepath);
	}
}

string Files::GetFileName(string filepathhash)
{
	string result;

	File filetemp(filepathhash);
	std::set<File>::const_iterator it = _files.find(filetemp);
	if (it != _files.end())
	{
		result = (*it).GetName();
	}
	else
	{
		throw runtime_error("File not found - filepathhash: " + filepathhash);
	}
	return result;
}

void Files::WriteToDisk()
{
	Operations op(::DBNAME);
	op.WriteFilesToDisk(_files);
}


void Files::Load()
{
	Operations op(::DBNAME);
	op.LoadFiles(_files);
}

