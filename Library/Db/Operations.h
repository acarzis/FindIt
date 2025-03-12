#pragma once

#include ".\IDatabase.h"
#include <string>
#include <set>
#include <mutex>

using namespace std;

class Operations : IDatabase
{
	string	_dbname;
	mutex	_mut;
	void CreateDbStructure();
	void InsertDefaultTableData();

public:
	Operations(string dbname);

	// Categories table
	void LoadCategories(list<Category> &categories) override;
	
	// ToScanQueue table
	void GetLatestToScanQueueItem(ToScanQueueItem& latestitem) override;
	void LoadToScanQueueItems(set<ToScanQueueItem>& toscanqueueitems) override;

	// Drives table
	void LoadDrives(list<Drive>& drives) override;

	// Folders table
	void LoadFolders(set<Folder>& folders) override;
};
