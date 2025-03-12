#include <list>
#include <mutex>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include <boost/filesystem.hpp>
#include "Operations.h"
#include "../Entities/Category.h"
#include "../Entities/Drive.h"
#include "../Entities/Folder.h"
#include "../Utils/DriveOperations.h"
#include "../Utils/Misc.cpp"

using namespace std;
namespace fs = boost::filesystem;

template <typename T>
class Monitor {
    // The object to be monitored
    T data;

    // Mutex to protect the object
    std::mutex mut;
public:
    // Default constructor
    Monitor<T>(T data = T{}) : data(data) {}

    // Function call operator
    // Argument is a callable object of type Func
    // which takes an argument of type T
    template <typename Func>
    auto operator() (Func func) {
        std::lock_guard<std::mutex> lck_guard(mut);

        // Call the function, protected by the lock
        return func(data);
    }
};


Operations::Operations(string dbname)
{
    _dbname = dbname;

    // create db if required
    fs::path path = fs::path(dbname);
    if (!exists(path))
    {
        CreateDbStructure();
        InsertDefaultTableData();
    }
}


void Operations::CreateDbStructure()
{
    try
    {
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database    db(_dbname, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        SQLite::Transaction transaction(db);

        string command = R"(
            CREATE TABLE Categories(
                Name text PRIMARY KEY,
                Extensions text NULL,
                FolderLocations text NULL)
            )";
        db.exec(command);

        command = R"(
            CREATE TABLE Drives(
                LogicalDrive text PRIMARY KEY,
                Name text NULL,
                ScanPriority bigint NOT NULL)
            )";
        db.exec(command);

        command = R"(
            CREATE TABLE Files(
                FullPathHash text PRIMARY KEY,
                Name text NULL,
                FileSize bigint NOT NULL,
                FolderHash text NULL,
                CategoryName text NULL)
            )";
        db.exec(command);                           // TO DO: add FK constraints

        command = R"(
            CREATE TABLE Folders(
                FullPathHash text PRIMARY KEY,
                Name text NULL,
                Path text NULL,
                LastModified text NOT NULL,
                LastChecked text NOT NULL,
                FolderSize bigint NOT NULL,
                CategoryName text NULL)
            )";
        db.exec(command);                           // TO DO: add FK constraints

        command = R"(
            CREATE TABLE ToScanQueue(
                Id bigint PRIMARY KEY,
                FullPathHash text NULL,
                Name text NULL,
                Path text NULL,
                Priority bigint NOT NULL)
            )";
        db.exec(command);

        transaction.commit();
    }

    catch (exception& e)
    {
        string temp = e.what();
        throw e;
    }
}

void Operations::InsertDefaultTableData()
{
    try
    {
        std::vector<std::string>    drives = DriveOperations::getListOfDrives();
        lock_guard<std::mutex>      lck_guard(_mut);
        SQLite::Database            db(_dbname, SQLite::OPEN_READWRITE);

        SQLite::Transaction transaction(db);

        for (string drive : drives)
        {
            string name;
            if (hasEnding(drive, "\\"))
            {
                drive = drive.substr(0, drive.size() - 1);
                wstring wdrive(drive.begin(), drive.end());
                name = DriveOperations::GetDriveDetails(wdrive);
            }

            string command = format("INSERT INTO Drives(LogicalDrive, Name, ScanPriority) VALUES (\"{}\", \"{}\", 0)", drive, name);
            db.exec(command);
        }
        transaction.commit();
    }

    catch (exception& e)
    {
        throw e;
    }
}


void Operations::LoadCategories(list<Category> &categories)
{
    try {
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname);
        SQLite::Statement       query(db, "SELECT * FROM Categories");

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
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname);
        SQLite::Statement       query(db, "SELECT * FROM ToScanQueue ORDER BY Id ASC LIMIT 1");

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
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname);
        SQLite::Statement       query(db, "SELECT * FROM ToScanQueue ORDER BY Id ASC");

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
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname);
        SQLite::Statement       query(db, "SELECT * FROM Drives");

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
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname);
        SQLite::Statement       query(db, "SELECT * FROM Folders");

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
