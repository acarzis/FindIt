#include "ToScanQueueItem.h"

ToScanQueueItem::ToScanQueueItem(int64_t id, string fullpathhash, string name, string path, int priority)
	: _Id(id), _FullPathHash(fullpathhash), _Name(name), _Path(path), _Priority(priority)
{
}

int64_t ToScanQueueItem::GetId()
{
	return _Id;
}

string ToScanQueueItem::GetFullPathHash()
{
	return _FullPathHash;
}

string ToScanQueueItem::GetPath()
{
	return _Path;
}

string ToScanQueueItem::GetName()
{
	return _Name;
}

int ToScanQueueItem::GetPriority()
{
	return _Priority;
}

bool ToScanQueueItem::operator< (const ToScanQueueItem& right) const
{
	return _Id < right._Id;
}
