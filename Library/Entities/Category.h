#pragma once

#include <string>

using namespace std;


class Category
{
    string _Name;
    string _Extension;
    string _FolderLocation;

public:
    Category(string name, string extensions, string folderlocations);
    string GetName();
    string GetExtensions();
    string GetFolderLocations();
};
