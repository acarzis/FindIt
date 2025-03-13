#pragma once

#include ".\IDatabase.h"
#include <string>
#include <set>
#include <mutex>

using namespace std;



class Operations : IDatabase
{
	static int		DBBULKINSERTROWS;
	string			_dbname;
	mutex			_mut;

	void CreateDbStructure();
	void InsertDefaultTableData();
	void DropTableData();

public:
	Operations(string dbname);
	void BackupDatabase();

	// Categories table
	void LoadCategories(list<Category> &categories) override;
	
	// ToScanQueue table
	void GetLatestToScanQueueItem(ToScanQueueItem& latestitem) override;
	void LoadToScanQueueItems(set<ToScanQueueItem>& toscanqueueitems) override;
	void WriteScanQueueToDisk(set<ToScanQueueItem>& scanqueueset);

	// Drives table
	void LoadDrives(list<Drive>& drives) override;

	// Files table
	void WriteFilesToDisk(set<File>& fileset);
	void LoadFiles(set<File>& files) override;

	// Folders table
	void LoadFolders(set<Folder>& folders) override;
	void WriteFoldersToDisk(set<Folder>& folderset);
};
