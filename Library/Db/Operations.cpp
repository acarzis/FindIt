#include <list>
#include <mutex>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include "Operations.h"
#include "../Entities/Category.h"
#include "../Entities/Drive.h"
#include "../Entities/Folder.h"
#include "../Utils/DriveOperations.h"
#include "../Utils/Misc.cpp"

using namespace std;
namespace fs = boost::filesystem;

int Operations::DBBULKINSERTROWS = 10000;

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

void Operations::BackupDatabase()
{
    // TO DO: Review this mechanism. 

    fs::path path = fs::path(_dbname);
    fs::path bak1 = fs::path(_dbname + ".BAK");
    fs::path bak2 = fs::path(_dbname + ".BAK2");

    try
    {
        if (fs::exists(bak1))
        {
            fs::copy_file(bak1, bak2, fs::copy_options::overwrite_existing);
        }
        fs::copy_file(path, bak1, fs::copy_options::overwrite_existing);
    }

    catch (exception &e)
    {
        cout << "BackupDatabase exception: " << e.what() << endl;

        if (fs::exists(bak1))
        {
            fs::copy_file(bak1, path, fs::copy_options::overwrite_existing);
        }
        else
        {
            if (fs::exists(bak2))
            {
                fs::copy_file(bak2, path, fs::copy_options::overwrite_existing);
            }
        }
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


        string name = "Music";
        string extensions = "mp3,wav,flac,m4a,vob,wma,aac";
        string command = format("INSERT INTO Categories(Name, Extensions, FolderLocations) VALUES (\"{}\", \"{}\", \"\")", name, extensions);
        db.exec(command);

        name = "Documents";
        extensions = "txt,doc,docx,pdf,htm,html,xls,xlsx,odt,ppt,pptx,rtf,wpd,log";
        command = format("INSERT INTO Categories(Name, Extensions, FolderLocations) VALUES (\"{}\", \"{}\", \"\")", name, extensions);
        db.exec(command);

        name = "Pictures";
        extensions = "jpeg,jpg,png,gif,tiff,bmp,webp,psd,raw";
        command = format("INSERT INTO Categories(Name, Extensions, FolderLocations) VALUES (\"{}\", \"{}\", \"\")", name, extensions);
        db.exec(command);

        name = "Videos";
        extensions = "mp4,mov,avi,wmv,flv,f4v,mkv,webm,avchd,mpeg,mpg,ogv,m4v";
        command = format("INSERT INTO Categories(Name, Extensions, FolderLocations) VALUES (\"{}\", \"{}\", \"\")", name, extensions);
        db.exec(command);

        transaction.commit();
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::DropTableData()
{
    try
    {
        lock_guard<std::mutex>      lck_guard(_mut);
        SQLite::Database            db(_dbname, SQLite::OPEN_READWRITE);

        SQLite::Transaction transaction(db);

        string command = "delete from files;";
        db.exec(command);

        command = "delete from folders;";
        db.exec(command);

        command = "delete from toscanqueue;";
        db.exec(command);

        transaction.commit();
    }

    catch (exception& e)
    {
        cout << "DropTableData exception: " << e.what() << endl;
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
            const int64_t foldersize = query.getColumn(5);
            const char* categoryname = query.getColumn(6);

            Folder f(fullpathhash, name, path, lastmodified, lastchecked, foldersize, categoryname);
            folders.insert(f);
        }
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::LoadFiles(set<File>& files)
{
    try {
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname);
        SQLite::Statement       query(db, "SELECT * FROM Files");

        while (query.executeStep())
        {
            const char* fullpathhash = query.getColumn(0);
            const char* name = query.getColumn(1);
            const int64_t filesize = query.getColumn(2);
            const char* folderhash = query.getColumn(3);
            const char* categoryname = query.getColumn(4);

            File f(fullpathhash, name, filesize, folderhash, categoryname);
            files.insert(f);
        }
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::WriteScanQueueToDisk(set<ToScanQueueItem> &scanqueueset)
{
    try
    {
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname, SQLite::OPEN_READWRITE);
        string insertdata;
        int64_t count = 0;
        string command = format("INSERT INTO ToScanQueue(Id, FullPathHash, Name, Path, Priority) VALUES ");

        for (ToScanQueueItem item : scanqueueset)
        {
            if (!insertdata.empty())
                insertdata += ",";

            ++count;
            insertdata += format("({}, \"{}\", \"{}\", \"{}\", \"{}\")", item.GetId(), item.GetFullPathHash(), item.GetName(), item.GetPath(), item.GetPriority());

            if (count % DBBULKINSERTROWS == 0)
            {
                string statement = command + insertdata;
                db.exec(statement);
                insertdata.clear();
            }
        }
        db.exec(command + insertdata);
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::WriteFoldersToDisk(set<Folder>& folderset)
{
    try
    {
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname, SQLite::OPEN_READWRITE);
        string insertdata;
        int64_t count = 0;
        string command = format("INSERT INTO Folders(FullPathHash, Name, Path, LastModified, LastChecked, FolderSize, CategoryName) VALUES ");

        for (Folder item : folderset)
        {
            if (!insertdata.empty())
                insertdata += ",";

            ++count;
            insertdata += format("(\"{}\", \"{}\", \"{}\", \"{}\", \"{}\", {}, \"{}\")", item.GetFullPathHash(), item.GetName(), item.GetPath(), 
                item.GetLastModified().ToUTCString(), item.GetLastChecked().ToUTCString(), item.GetFolderSize(), item.GetCategory());

            if (count % DBBULKINSERTROWS == 0)
            {
                string statement = command + insertdata;
                db.exec(statement);
                insertdata.clear();
            }
        }
        db.exec(command + insertdata);
    }

    catch (exception& e)
    {
        throw e;
    }
}

void Operations::WriteFilesToDisk(set<File>& fileset)
{
    try
    {
        lock_guard<std::mutex>  lck_guard(_mut);
        SQLite::Database        db = SQLite::Database(_dbname, SQLite::OPEN_READWRITE);
        string insertdata;
        int64_t count = 0;
        string command = format("INSERT INTO Files(FullPathHash, Name, FileSize, FolderHash, CategoryName) VALUES ");

        for (File item : fileset)
        {
            if (!insertdata.empty())
                insertdata += ",";

            ++count;
            insertdata += format("(\"{}\", \"{}\", {}, \"{}\", \"{}\")", item.GetFullPathHash(), item.GetName(),
                item.GetFilesize(), item.GetFolderHash(), item.GetCategoryName());

            if (count % DBBULKINSERTROWS == 0)
            {
                string statement = command + insertdata;
                db.exec(statement);
                insertdata.clear();
            }
        }
        db.exec(command + insertdata);
    }

    catch (exception& e)
    {
        throw e;
    }
}
