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
#include "../Library/InMemoryDB/Folders.h"
#include "../Library/InMemoryDB/Files.h"
#include "../Library/Utils/DateTime.h"
#include "../Library/Globals/constants.cpp"
#include "../Library/Db/Operations.h"


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

		int count = 0;
		while (++count) {
			TimerJob();
			std::this_thread::sleep_for(std::chrono::microseconds(10));

			if (count >= DBPERSISTENCEINTERVAL)
			{
				cout << "Performing db backup ... " << endl;

				count = 0;
				Operations op(::DBNAME);
				op.BackupDatabase();
				op.DropTableData();
				ToScanQueue::GetInstance().WriteToDisk();
				Folders::GetInstance().WriteToDisk();
				Files::GetInstance().WriteToDisk();
			}
		}

		DateTime point1;
		cout << "Point1: " << point1.ToUTCString() << endl;

		ToScanQueue::GetInstance().WriteToDisk();

		DateTime point2;
		cout << "Point2: " << point2.ToUTCString() << endl;

		Folders::GetInstance().WriteToDisk();

		DateTime point3;
		cout << "Point3: " << point2.ToUTCString() << endl;

		Files::GetInstance().WriteToDisk();

		DateTime point4;
		cout << "Point4: " << point2.ToUTCString() << endl;

	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
	return 0;
}
