#pragma once

#include ".\IDatabase.h"
#include <string>
#include <set>

using namespace std;

class Operations : IDatabase
{
	string _dbname;

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
	// void AddFolder(Folder& folder) const override;
};
