#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include "../../Library/Entities/ToScanQueueItem.h"
#include "../../Library/InMemoryDB/ToScanQueue.h"


TEST(ToScanQueue, DoubleInsert)
{
	ToScanQueue &queue = ToScanQueue::GetInstance();
	ToScanQueueItem item1(100, "fullpathhash", "name", "path", 0);

	size_t before = queue.GetQueueSize();
	queue.AddPathToScanQueue("C:\\Windows111", 2);
	queue.AddPathToScanQueue("C:\\Windows111", 3);
	size_t after = queue.GetQueueSize();
	
	ASSERT_EQ(1, after - before);


	ToScanQueue& nextitemtoprocess = ToScanQueue::GetInstance();
	ToScanQueueItem qi;
	before = nextitemtoprocess.GetQueueSize();
	nextitemtoprocess.GetNextQueueItem(qi);
	nextitemtoprocess.RemoveQueueItem(qi.GetId());
	after = nextitemtoprocess.GetQueueSize();
	ASSERT_EQ(1, before - after);
}

