#pragma once

#include <string>
#include <list>
#include "../../Entities/Category.h"

using namespace std;

class ICategories
{
	virtual list<Category> GetCategories() = 0;
	virtual void AddCategory(string name, list<string> extensionlist) = 0;
	virtual bool CategoryExists(string category, Category& cat) = 0;
};

