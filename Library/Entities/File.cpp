#include "File.h"
#include <boost/filesystem.hpp>
#include "../Utils/Encryption.h"

using namespace std;
namespace fs = boost::filesystem;


File::File(string fullpath, int64_t filesize, string categoryname) :
	_CategoryName(categoryname), _Name(fs::path(fullpath).filename().string()), _FileSize(filesize),
	_FullPathHash(SHA256HashString(fullpath)), _FolderHash(SHA256HashString(fs::path(fullpath).parent_path().string()))
{
}

File::File(string fullpathhash, string name, int64_t filesize, string folderhash, string categoryname) :
	_CategoryName(categoryname), _Name(name), _FileSize(filesize), _FullPathHash(fullpathhash), _FolderHash(folderhash)
{
}

File::File(string fullpathhash) :
	_FullPathHash(fullpathhash), _FileSize(0)
{
}

bool File::operator< (const File& right) const
{
	return _FullPathHash < right._FullPathHash;
}

int64_t File::GetFilesize() const
{
	return _FileSize;
}

string File::GetName() const
{
	return _Name;
}

string File::GetFullPathHash() const
{
	return _FullPathHash;
}

string File::GetFolderHash() const
{
	return _FolderHash;
}

string File::GetCategoryName() const
{
	return _CategoryName;
}
