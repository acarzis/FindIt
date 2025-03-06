#include <string>
#include <list>
#include <boost/filesystem.hpp>
#include "DriveOperations.h"

using namespace std;
namespace fs = boost::filesystem;

void DriveOperations::EnumerateFolders(string fullpath, list<string>& folderlist)
{
    try
    {
        fs::path p(fullpath);
        fs::directory_iterator end_itr;
        for (fs::directory_iterator itr(p); itr != end_itr; ++itr)      // top level only, not recursive
        {
            if (is_directory(itr->path()))
            {
                folderlist.push_back(itr->path().string());
            }
        }
    }
    catch (exception& e)
    {
    }
}

void DriveOperations::EnumerateFiles(string fullpath, list<string>& filelist)
{
    try
    {
        fs::path p(fullpath);
        fs::directory_iterator end_itr;
        for (fs::directory_iterator itr(p); itr != end_itr; ++itr)      // top level only, not recursive
        {
            if (!is_directory(itr->path()))
            {
                filelist.push_back(itr->path().string());
            }
        }
    }
    catch (exception& e)
    {
    }
}

uintmax_t DriveOperations::Filesize(string fullpath)
{
    try
    {
        fs::path p(fullpath);
        if (is_regular_file(p))
        {
            return fs::file_size(p);
        }
    }
    catch (exception& e)
    {
    }
    return 0;
}

DateTime DriveOperations::GetLastWriteTime(string foldername)
{
    DateTime result;

    try
    {
        fs::path directoryinfo(foldername);
        if (fs::is_directory(directoryinfo))
        {
            result = DateTime(fs::last_write_time(directoryinfo));
        }
    }

    catch (exception& e)
    {
    }
    return result;
}
