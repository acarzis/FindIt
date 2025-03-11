#pragma once

#include "../../Library/InMemoryDB/Files.h"


class FilesT : public Files
{
public:
	set<File>& GetFilesSet();
	int64_t GetFilesCount();
};
