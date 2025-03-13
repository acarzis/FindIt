#pragma once

#include <set>
#include <map>
#include "./Interfaces/IToScanQueue.h"
#include "../Globals/constants.h"


using namespace std;

class ToScanQueue : public IToScanQueue
{
    ToScanQueue();
    int64_t _currentId;
	set<ToScanQueueItem> _toscanqueue;          // ordered by id
    map<string, int64_t> _itemmap;              // map fullpath hash - item id   

public:
    static ToScanQueue& GetInstance();
    void Load();
    void WriteToDisk();
    void AddPathToScanQueue(std::string fullpath, int priority) override;
    void GetNextQueueItem(ToScanQueueItem& qi) override;
    size_t GetQueueSize() override;
    void RemoveQueueItem(int64_t queueId) override;
    bool PathExistsInScanQueue(std::string fullpath) override;
};
