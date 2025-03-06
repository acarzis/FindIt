
overall design:

	we need classes that load and save db table data
		- one entry/row at a time
		- bulk loading/saving
	we need classes that add/remove items from in memory db
	we need classes that load data from the db into the in-memory db 
	we need classes that save data from the in-memory db to the db


upon startup, the in-memory database calls the Database layer to get/load the data.


required packages/libraries:
vcpkg install sqlitecpp
vcpkg install gtest
