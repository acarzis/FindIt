#include "Code.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include "../Library/Entities/Category.h"
#include "../Library/Entities/Folder.h"
#include "../Library/Utils/DateTime.h"
#include "../Library/InMemoryDB/Drives.h"
#include "../Library/InMemoryDB/ToScanQueue.h"
#include "../Library/InMemoryDB/Categories.h"
#include "../Library/InMemoryDB/Folders.h"
#include "../Library/Utils/DriveOperations.h"
#include "../Library/InMemoryDB/Files.h"
#include "../Library/InMemoryDB/FolderManager.h"


using namespace std;
namespace fs = boost::filesystem;

list<Drive> driveList;
list<Category> categoryList;
list<tuple<string, string>> categoryExtensions;             // extension, category name
list<tuple<string, string>> categoryPaths;                  // fullpath, category name
std::vector<std::string> drives;                            // drives on the PC, includes network/mapped drives


void Init()
{
    drives = DriveOperations::getListOfDrives();

    Drives d = Drives::GetInstance();
    d.Load();
    d.GetDriveList(driveList);

    ToScanQueue& toscanqueue = ToScanQueue::GetInstance();
    // omitted while testing
    // toscanqueue.Load();

    Categories& categories = Categories::GetInstance();
    categories.Load();
    categoryList = categories.GetCategories();

    // omitted while testing
    // add drive list to the scanqueue
    /*
    for (Drive drive : driveList)
    {   
        toscanqueue.AddPathToScanQueue(drive.GetLogicalDriveName(), 3);      // TO DO: create priority enums 
    }
    */

    // testing code: 
    toscanqueue.AddPathToScanQueue(DriveOperations::UNCPath("Z:"), 2);      // TO DO: create priority enums 
    // toscanqueue.AddPathToScanQueue("c:\\AMD\\AMD-Software-Adrenalin-Edition-24.2.1-combined-MinimalSetup-240223_web", 2);      // TO DO: create priority enums 


    // below should be done every hour
    for (list<Category>::const_iterator it = categoryList.begin(); it != categoryList.end(); ++it)
    {
        Category c = *it;
        stringstream ss(c.GetExtensions());
        std::vector<std::string> tokens;
        string temp;
        char del = ',';
        std::tuple<string, string> t;
        while (getline(ss, temp, del)) {
            t = std::make_tuple(temp, c.GetName());         // extension - category name
            categoryExtensions.push_back(t);
        }

        stringstream ss1(c.GetFolderLocations());
        tokens.clear();
        while (getline(ss1, temp, del)) {
            if (!temp.empty())
            {
                t = std::make_tuple(temp, c.GetName());     // fullpath - category name
                categoryPaths.push_back(t);
            }
        }
    }
};

void TimerJob()
{
    bool addedtoQueue = false;

    try
    {
        int64_t fldrsize;
        string foldercategory;
        DateTime lastchecked, lastmodified, lastwritetime;
        DateTime now;  // ToString format: 2025-03-20 22:04:39

        ToScanQueueItem qi;
        ToScanQueue& nextitemtoprocess = ToScanQueue::GetInstance();
        nextitemtoprocess.GetNextQueueItem(qi);

        // testing code :
        // qi = ToScanQueueItem(qi.GetId(), qi.GetFullPathHash(), "", "c:\\windows", qi.GetPriority());

        fs::path file(qi.GetName());
        fs::path dir(qi.GetPath());
        std::string fullpath = dir.append(file).string();


        if (fullpath == "")
        {
            // test code 

            string path = DriveOperations::UNCPath("Z:");

            cout << "nothing to process" << endl;

            DateTime before1;
            fldrsize = 0;
            cout << "Before: " << before1.ToUTCString() << endl;

            /*
            fldrsize = Folders::GetInstance().ComputeFolderSize("C:\\Users\\Default");
            DateTime after1;
            cout << "After: " << after1.ToUTCString() << " Folder size: " << fldrsize << endl;
            */

            fldrsize = Folders::GetInstance().ComputeFolderSizeInternally(path);
            DateTime after1;
            cout << "After: " << after1.ToUTCString() << " Folder size: " << fldrsize << endl;

            DateTime after2;
            cout << "Number of folders: " << FolderManager::GetInstance().GetFolderCount(path) << endl;
            cout << "After2: " << after2.ToUTCString() << endl;

            DateTime after3;
            cout << "Number of files: " << FolderManager::GetInstance().GetFileCount(path) << endl;
            cout << "After3: " << after3.ToUTCString() << endl;

            Folders::GetInstance().GetFolderDetails(path, foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "Folder " << "C:\\Users\\acarz" << " size: " << fldrsize << " last checked: " << lastchecked.ToUTCString()
                << " last modified: " << lastmodified.ToUTCString() << endl;

            /*
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Libraries");
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Public Account Pictures");
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Public Desktop");
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Public Documents");
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Public Music");
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Public Pictures");
            FolderManager::GetInstance().AddChildFolder("D:\\Users\\Public", "Public Videos");
            */

            DateTime after4;
            cout << "After4: " << after3.ToUTCString() << endl;
            cout << "ComputeParentFolderSize: " << FolderManager::GetInstance().ComputeParentFolderSize(path) << endl;

            DateTime after5;
            cout << "After5: " << after3.ToUTCString() << endl;

            return;


            // test code:
            Folders& fold = Folders::GetInstance();
            Files& files = Files::GetInstance();
            fold.GetFolderDetails("c:\\AMD\\AMD-Software-Adrenalin-Edition-24.2.1-combined-MinimalSetup-240223_web", foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "1 " << fldrsize << endl;

            fold.GetFolderDetails("c:\\AMD\\AMDSoftwareInstaller", foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "2 " << fldrsize << endl;

            fold.GetFolderDetails("c:\\AMD\\Chipset_Driver_Installer", foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "3 " << fldrsize << endl;

            fold.GetFolderDetails("c:\\AMD\\Chipset_Installer", foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "4 " << fldrsize << endl;

            fold.GetFolderDetails("c:\\AMD\\Chipset_Software", foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "5 " << fldrsize << endl;

            fold.GetFolderDetails("c:\\AMIGADEV", foldercategory, fldrsize, lastchecked, lastmodified);
            cout << "6 " << fldrsize << endl;


            fldrsize = 0;
            fldrsize = fold.ComputeFolderSize("c:\\AMD\\AMD-Software-Adrenalin-Edition-24.2.1-combined-MinimalSetup-240223_web");
            cout << "11 " << fldrsize << endl;
            cout << "Number of folders: " << fold.GetCount("c:\\AMD\\AMD-Software-Adrenalin-Edition-24.2.1-combined-MinimalSetup-240223_web") << endl;
            cout << "Number of files: " << files.GetCount() << endl;

            fldrsize = 0;
            fldrsize = fold.ComputeFolderSize("c:\\AMD\\AMDSoftwareInstaller");
            cout << "12 " << fldrsize << endl;

            fldrsize = 0;
            fldrsize = fold.ComputeFolderSize("c:\\AMD\\Chipset_Driver_Installer");
            cout << "13 " << fldrsize << endl;

            fldrsize = 0;
            fldrsize = fold.ComputeFolderSize("c:\\AMD\\Chipset_Installer");
            cout << "14 " << fldrsize << endl;

            fldrsize = 0;
            fldrsize = fold.ComputeFolderSize("c:\\AMD\\Chipset_Software");
            cout << "15 " << fldrsize << endl;

            fldrsize = 0;
            DateTime before;
            cout << "Before: " << before.ToUTCString() << endl;
            fldrsize = fold.ComputeFolderSize("c:\\Users");
            DateTime after;
            cout << "After: " << after.ToUTCString() << endl;
            cout << "16 " << fldrsize << endl;
            cout << "Number of folders: " << fold.GetCount("c:\\Users") << " , # folders: " << FolderManager::GetInstance().GetFolderCount("c:\\Users") << endl;
            cout << "Number of files: " << FolderManager::GetInstance().GetFileCount("c:\\Users") << endl;

            return;
        }

        cout << "processing folder: " << fullpath << endl;

        try
        {
            fs::path directoryinfo(fullpath);
            if (fs::is_directory(directoryinfo))
            {
                lastwritetime = DateTime(fs::last_write_time(directoryinfo));
            }

            bool exists = false;
            Folders& fold = Folders::GetInstance();
            Folder fullpathfolder;
            if (fold.FolderExists(fullpath, fullpathfolder))
            {
                lastmodified = fullpathfolder.GetLastModified();
                exists = true;
            }

            if ((lastwritetime >= lastmodified) || (!exists))
            {
                list<string> filelist;
                DriveOperations::EnumerateFiles(fullpath, filelist);

                uintmax_t filelistSize = 0;
                for (string f : filelist)
                {
                    try
                    {
                        fs::path path(f);   // f = foldername + filename
                        string catstr;
                        string fileextension = path.extension().string();
                        tuple<string, string> extCatname = make_tuple(fileextension, "");
                        auto ce = find_if(categoryExtensions.begin(), categoryExtensions.end(),
                            [extCatname](tuple<string, string> t) -> bool {
                                if (get<0>(t) == get<0>(extCatname)) {
                                    return true;
                                }
                                return false;
                            });

                        if (ce != std::end(categoryExtensions))
                        {
                            catstr = get<1>(*ce);
                        }

                        uintmax_t fsize = DriveOperations::Filesize(f);
                        filelistSize += fsize;

                        Files& files = Files::GetInstance();
                        files.AddFile(path.parent_path().string(), path.filename().string(), "", catstr, fsize); // creates folder if required
                    }
                    catch (exception& e)
                    {
                        cout << "Exception while processing file " << f << " - " << e.what() << endl;
                    }
                }

                if (filelist.size() == 0)
                {
                    fold.AddFolder(fullpath, "", 0);
                }

                // add all the sub-folders
                list<string> folderlist;
                DriveOperations::EnumerateFolders(fullpath, folderlist);

                if (folderlist.size() == 0)
                {
                    // we have no sub-folders, compute size of parent folder
                    DateTime now;
                    fold.AddFolderDetails(fullpath, "", filelistSize, now, false);

                    // get parent folder
                    /*
                    fs::path fp(fullpath);
                    int64_t foldersize = 0;
                    foldersize = fold.ComputeFolderSize(fp.parent_path().string());     // problem here. very slow
                    if (foldersize > 0)
                    {
                        fold.AddFolderDetails(fp.parent_path().string(), "", foldersize, now, false);
                    }
                    */
                }

                for (string f : folderlist)
                {
                    bool exists = false;
                    lastmodified = DateTime();
                    lastwritetime = DateTime();
                    if (fold.FolderExists(f, fullpathfolder))
                    {
                        DateTime lastchecked;
                        string foldercategory;
                        exists = true;
                        fold.GetFolderDetails(f, foldercategory, fldrsize, lastchecked, lastmodified);
                    }

                    DateTime lastwritetime = DriveOperations::GetLastWriteTime(fullpath);
                    if ((lastwritetime >= lastmodified) || (!exists))
                    {
                        nextitemtoprocess.AddPathToScanQueue(f, 2);         // TO DO: use enum constants

                        // cout << "Adding to scan queue " << f << endl;
                    }
                    fold.AddFolderDetails(f, "", 0, lastwritetime, true);
                    FolderManager::GetInstance().AddChildFolder(fullpath, fs::path(f).filename().string());
                }
            }

            cout << "Number of items in queue: " << nextitemtoprocess.GetQueueSize() << endl;
            cout << "Number of folders: " << fold.GetCount() << endl;
            cout << "Number of files: " << Files::GetInstance().GetCount() << endl;

        }
        catch (exception& e)
        {
            cout << "Exception while processing folder  " << fullpath << e.what() << endl;
        }

        // add the folder's category if available
        // categoryPaths = list of tuples <fullpath, category name>
        tuple<string, string> pathseacrh = make_tuple(fullpath, "");
        auto ce = find_if(categoryPaths.begin(), categoryPaths.end(),
            [pathseacrh](tuple<string, string> t) -> bool {
                if (get<0>(pathseacrh).find(get<0>(t)) != string::npos) {
                    return true;
                }
                return false;
            });

        if (ce != std::end(categoryPaths))
        {
            string catstr = get<1>(*ce);
            Folders::GetInstance().AddFolderDetails(fullpath, catstr, 0, now, true);
        }

        nextitemtoprocess.RemoveQueueItem(qi.GetId());
        int breakpoint = 0;
    }

    catch (exception& e)
    {
        cout << "TimerJob exception " << e.what() << endl;
    };
};

