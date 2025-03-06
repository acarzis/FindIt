#include <list>
#include <SQLiteCpp/Database.h>
#include "Operations.h"
#include "../Entities/Category.h"
#include "../Entities/Drive.h"
#include "../Entities/Folder.h"

using namespace std;

Operations::Operations(string dbname)
{
    _dbname = dbname;
}

void Operations::LoadCategories(list<Category> &categories)
{
    try {
        SQLite::Database    db = SQLite::Database(_dbname);
        SQLite::Statement   query(db, "SELECT * FROM Categories");

        while (query.executeStep())
        {
            const char* name = query.getColumn(0);
            const char* extension = query.getColumn(1);
            const char* folderlocation = query.getColumn(2);

            Category c(name, extension, folderlocation);
            categories.push_back(c);
        }
    }

    catch (exception &e)
    {
        throw e;
    }
}

void Operations::GetLatestToScanQueueItem(ToScanQueueItem& latestitem)
{
    try {
        SQLite::Database    db = SQLite::Database(_dbname);
        SQLite::Statement   query(db, "SELECT * FROM ToScanQueue ORDER BY Id ASC LIMIT 1");

        while (query.executeStep())
        {
            const int64_t id = query.getColumn(0);
            const char* fullpathhash = query.getColumn(1);
            const char* name = query.getColumn(2);
            const char* path = query.getColumn(3);
            const int priority = query.getColumn(4);

            ToScanQueueItem s(id, fullpathhash, name, path, priority);
            latestitem = s;
        }
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::LoadToScanQueueItems(set<ToScanQueueItem>& toscanqueueitems)
{
    try {
        SQLite::Database    db = SQLite::Database(_dbname);
        SQLite::Statement   query(db, "SELECT * FROM ToScanQueue ORDER BY Id ASC");

        while (query.executeStep())
        {
            const int64_t id = query.getColumn(0);
            const char* fullpathhash = query.getColumn(1);
            const char* name = query.getColumn(2);
            const char* path = query.getColumn(3);
            const int priority = query.getColumn(4);

            ToScanQueueItem s(id, fullpathhash, name, path, priority);
            toscanqueueitems.insert(s);
        }
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::LoadDrives(list<Drive>& drives)
{
    try {
        SQLite::Database    db = SQLite::Database(_dbname);
        SQLite::Statement   query(db, "SELECT * FROM Drives");

        while (query.executeStep())
        {
            const char* logicaldrive = query.getColumn(0);
            const char* name = query.getColumn(1);
            const int priority = query.getColumn(2);

            Drive d(logicaldrive, name, priority);
            drives.push_back(d);
        }
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::LoadFolders(set<Folder>& folders)
{
    try {
        SQLite::Database    db = SQLite::Database(_dbname);
        SQLite::Statement   query(db, "SELECT * FROM Folders");

        while (query.executeStep())
        {
            const char* fullpathhash = query.getColumn(0);
            const char* name = query.getColumn(1);
            const char* path = query.getColumn(2);
            const char* lastmodified = query.getColumn(3);
            const char* lastchecked = query.getColumn(4);
            const int foldersize = query.getColumn(5);

            Folder f(fullpathhash, name, path, lastmodified, lastchecked, foldersize);
            folders.insert(f);    // FAILS TODO
        }
    }

    catch (exception& e)
    {
        throw e;
    }
}
