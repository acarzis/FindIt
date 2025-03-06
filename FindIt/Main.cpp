// FindIt.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "Code.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Database.h>
#include "../Library/Entities/ToScanQueueItem.h"
#include "../Library/InMemoryDB/Categories.h"
#include "../Library/InMemoryDB/ToScanQueue.h"

using namespace std;


int main()
{
	cout << "Starting Up ..." << endl;

	try {
		Categories cats = Categories::GetInstance();
		cats.Load();
		list<Category> c = cats.GetCategories();

		for (Category cat : c)
		{
			cout << "name: " << cat.GetName() << " extension: " << cat.GetExtensions() << " folder location: " << cat.GetFolderLocations() << endl;
		}
	}

	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}

	try
	{
		/*
		ToScanQueue q = ToScanQueue::GetInstance();
		q.Load();
		ToScanQueueItem qi;
		q.GetNextQueueItem(qi);
		cout << "id: " << qi.GetId() << " name: " << qi.GetName() << " priority: " << qi.GetPriority() << " fullpath hash: " << qi.GetFullPathHash() << endl;


		q.AddPathToScanQueue("D:\\DEVELOPMENT\\vcpkg\\packages\\boost-config_x64-windows\\share\\boost_config", 2);
		*/
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}


	try
	{
		Init();

		while (1) {
			TimerJob();
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
	return 0;
}
