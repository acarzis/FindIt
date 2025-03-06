#pragma once

#include <string>

using namespace std;

class ToScanQueueItem
{
    int64_t _Id = {0};
    string _FullPathHash;
    string _Name;
    string _Path;
    int _Priority = {0};

public:
    ToScanQueueItem() = default;
    ToScanQueueItem(int64_t id, string fullpathhash, string name, string path, int priority);
    int64_t GetId();
    string GetFullPathHash();
    string GetPath();
    string GetName();
    int GetPriority();
    bool operator< (const ToScanQueueItem& right) const;
};
