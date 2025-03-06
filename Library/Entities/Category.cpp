#include "Category.h"

Category::Category(string name, string extensions, string folderlocations)
	: _Name(name), _Extension(extensions), _FolderLocation(folderlocations)
{
}

string Category::GetName()
{
	return _Name;
}

string Category::GetExtensions()
{
	return _Extension;
}

string Category::GetFolderLocations()
{
	return _FolderLocation;
}
