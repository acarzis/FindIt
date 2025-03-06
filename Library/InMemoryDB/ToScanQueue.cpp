#include "ToScanQueue.h"
#include "../Db/Operations.h"
#include "../Globals/constants.h"
#include "../Utils/Encryption.h"
#include <boost/filesystem.hpp>

extern std::string DBNAME;

using namespace std;
namespace fs = boost::filesystem;

ToScanQueue::ToScanQueue() : _currentId(0)
{
}

ToScanQueue& ToScanQueue::GetInstance()
{
	static ToScanQueue _instance;
	return _instance;
}

void ToScanQueue::Load()
{	
	Operations op(::DBNAME);
	op.LoadToScanQueueItems(_toscanqueue);

	if (_toscanqueue.size() > 0)
	{
		auto q = *_toscanqueue.begin();
		_currentId = q.GetId();
	}
}

void ToScanQueue::AddPathToScanQueue(std::string fullpath, int priority)
{
	std::string name = fs::path(fullpath).filename().string();
	std::string path = fs::path(fullpath).parent_path().string();

	pair<string, int64_t> mapentry = make_pair(SHA256HashString(fullpath), _currentId);
	if (_itemmap.insert(mapentry).second == true)
	{
		ToScanQueueItem t(++_currentId, SHA256HashString(fullpath), name, path, priority);
		_toscanqueue.insert(t);
	}
}

void ToScanQueue::GetNextQueueItem(ToScanQueueItem &qi)
{
	ToScanQueueItem t;
	if (_toscanqueue.size() > 0)
	{
		auto t = _toscanqueue.begin();
		qi = *t;
	}
}

size_t ToScanQueue::GetQueueSize()
{
	return _toscanqueue.size();
}

void ToScanQueue::RemoveQueueItem(int64_t queueId)
{
	ToScanQueueItem tofind(queueId, "fullpathhash", "name", "path", 0);
	auto it = _toscanqueue.find(tofind);
	if (it != _toscanqueue.end())
	{
		ToScanQueueItem item = (*it);
		item.GetFullPathHash();
		
		auto it2 = _itemmap.find(item.GetFullPathHash());
		if (it2 != _itemmap.end())
		{
			_itemmap.erase(it2);
		}
		_toscanqueue.erase(it);
	}
}

bool ToScanQueue::PathExistsInScanQueue(std::string fullpath)
{
	if (_itemmap.find(SHA256HashString(fullpath)) != _itemmap.end())
		return true;

	return false;
}
