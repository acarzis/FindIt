#include "Categories.h"
#include "../Db/Operations.h"

extern string DBNAME;

Categories::Categories()
{

}

Categories& Categories::GetInstance()
{
	static Categories _instance;
	return _instance;
}

void Categories::Load()
{
	Operations op(::DBNAME);
	op.LoadCategories(_categories);
}


list<Category> Categories::GetCategories()
{
	return _categories;
}

void Categories::AddCategory(string name, list<string> extensionlist)
{

}

bool Categories::CategoryExists(string category, Category& cat)
{
	return false;
}

