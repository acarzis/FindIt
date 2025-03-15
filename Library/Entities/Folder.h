#pragma once

#include <string>
#include "Category.h"
#include "../Utils/DateTime.h"

using namespace std;

class Folder
{
    string _FullPathHash;
    string _Path;
    string _Name;
    string _CategoryName;
    DateTime _LastModified;
    DateTime _LastChecked;
    int64_t _FolderSize = {0};

    // foreign key - TO DO
    // Category &Category;

public:
    Folder();
    Folder(string fullpathhash, string name, string path, string lastmodified, string lastchecked, int64_t foldersize, string category);
    bool operator< (const Folder& right) const;
    string GetFullPathHash() const;
    string GetName() const;
    string GetPath() const;
    string GetCategory() const;
    int64_t GetFolderSize() const;
    DateTime GetLastChecked() const;
    DateTime GetLastModified() const;
    void SetFolderSize(int64_t foldersize);
    void SetCategoryName(string categoryname);
    void SetLastChecked(DateTime lastcheckedtime);
    void SetLastModified(DateTime lastmodified);
};
