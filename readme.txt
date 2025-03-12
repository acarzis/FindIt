

FindIt - A C++ re-implementation of my EnumerateFolders C# project

This project is a work in progress. A lot of work is still required. 


Goal: I want a Windows file search/indexer that is quick, supports all my network drives, does not require me searching by each folder/drive 
individually, and can track drive space usage by document type, folder, drive.


Changes from EnumerateFolders project: 

Rather than relying on data being stored and accessed from the file system and the DB, all data is stored in memory/data structures and is accessed from therein during normal operation.


Currently working on:  App startup and DB persistence code
