#pragma once

#include <list>
#include "../Entities/Category.h"
#include "./Interfaces/ICategories.h"

using namespace std;


class Categories : public ICategories
{
	list<Category> _categories;
	Categories();

public:
	void Load();
	static Categories& GetInstance();
	list<Category> GetCategories() override;
	void AddCategory(string name, list<string> extensionlist) override;
	bool CategoryExists(string category, Category& cat) override;
};
