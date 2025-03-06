

FindIt - A C++ re-implementation of my EnumerateFolders C# project

This project is a work in progress. A lot of work is still required. 

Goal: I want a Windows file search/indexer that is quick, supports all my network drives, does not require me searching by each folder/drive individually, 
and can track drive space usage by document type, folder, drive.

Changes from EnumerateFolders project: 

Rather than relying on data being stored and accessed from the file system and the DB, all data is stored in memory/data structures and is accessed from therein during normal operation.

There is no DB persistence layer yet. But the intent is to load data from a db on application startup and to synchronize the in-memory data with the db periodically.

Note: Some of the code relies on a db and associated code with the same db structure as present in the EnumerateFolders project.

EnumerateFolders was too slow in indexing my data. I did not do an analysis as to the cause. Perhaps some of my indexing or search algorithms were inefficient or the constant 
db 'hitting' was the issue. Regardless, this new approach should be better. Furthermore, I am putting more effort in doing a better job testing and running performance metrics.


