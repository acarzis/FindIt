#pragma once

#include <list>
#include <set>
#include "../Entities/Category.h"
#include "../Entities/ToScanQueueItem.h"
#include "../Entities/Drive.h"
#include "../Entities/Folder.h"


using namespace std;

class IDatabase
{
	virtual void LoadCategories(list<Category> &categories) = 0;
	virtual void GetLatestToScanQueueItem(ToScanQueueItem &latestitem) = 0;
	virtual void LoadToScanQueueItems(set<ToScanQueueItem>& toscanqueueitems) = 0;
	virtual void LoadDrives(list<Drive>& drives) = 0;
	virtual void LoadFolders(set<Folder>& folders) = 0;
	// virtual void AddFolder(Folder& folder) const = 0;
};
