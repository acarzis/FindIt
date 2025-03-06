#include <set>
#include "../../Entities/File.h"

using namespace std;

class IFiles
{
	virtual void AddFile(string folderpath, string filepath, string foldercategory = "", string filecategory = "", int64_t filesize = 0) = 0;
	virtual void AddFileDetails(string filepath, string category, int64_t filesize) = 0;
	virtual set<File>& GetAllFiles() = 0;
};
