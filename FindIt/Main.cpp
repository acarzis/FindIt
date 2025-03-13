#include "Main.h"
#include "Code.h"
#include <string>
#include <iostream>
#include <thread>
#include "../Library/InMemoryDB/ToScanQueue.h"
#include "../Library/InMemoryDB/Folders.h"
#include "../Library/InMemoryDB/Files.h"
#include "../Library/Globals/constants.cpp"
#include "../Library/Db/Operations.h"


using namespace std;


int main()
{
	cout << "Starting Up ..." << endl;

	try
	{
		Init();

		int count = 0;
		while (++count) {
			TimerJob();
			std::this_thread::sleep_for(std::chrono::microseconds(1));

			if (count >= DBPERSISTENCEINTERVAL)
			{
				cout << "Performing db backup to file " << ::DBNAME << " ..." << endl;

				count = 0;
				Operations op(::DBNAME);
				op.BackupDatabase();
				op.DropTableData();
				ToScanQueue::GetInstance().WriteToDisk();
				Folders::GetInstance().WriteToDisk();
				Files::GetInstance().WriteToDisk();
			}
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
	return 0;
}
