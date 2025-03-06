#pragma once

#include <string>
#include "../../Entities/ToScanQueueItem.h"

using namespace std;

class IToScanQueue
{
    virtual void AddPathToScanQueue(std::string fullpath, int priority) = 0;
    virtual void GetNextQueueItem(ToScanQueueItem& qi) = 0;
    virtual size_t GetQueueSize() = 0;
    virtual void RemoveQueueItem(int64_t queueId) = 0;
    virtual bool PathExistsInScanQueue(std::string fullpath) = 0;
};
