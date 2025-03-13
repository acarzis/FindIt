#pragma once

#include <set>
#include "./Interfaces/IFiles.h"

using namespace std;

class Files : public IFiles
{
public:
	static Files& GetInstance();
	virtual void AddFile(string dirname, string fname, string foldercategory = "", string filecategory = "", int64_t filesize = 0) override;
	virtual void AddFileDetails(string filepath, string category, int64_t filesize) override;
	virtual set<File>& GetAllFiles() override;
	int64_t GetCount();
	void GetFile(string filepath, File& file);
	string GetFileName(string filepathhash);
	void Load();
	void WriteToDisk();

protected:
	set<File> _files;			// sorted by File::_FullPathHash
};
