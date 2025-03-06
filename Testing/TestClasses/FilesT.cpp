#include "FilesT.h"
#include <set>

set<File>& FilesT::GetFilesSet()
{
	return _files;
}

int64_t FilesT::GetFilesCount()
{
	return _files.size();
}

