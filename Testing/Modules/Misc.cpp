#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <list>
#include "../../Library/InMemoryDB/Categories.h"
#include "../../Library/Entities/File.h"
#include "../../Library/InMemoryDB/Folders.h"
#include "../../Library/InMemoryDB/Files.h"
#include "../TestClasses/FilesT.h"

using namespace std;
namespace fs = boost::filesystem;


TEST(Misc, AddFileTwice)
{
    string dirname = "c:\\windows";
    string fname = "readme.txt";
    string filecategory;
    int64_t filesize = 0;

    Files& files = Files::GetInstance();
    size_t countbefore = files.GetCount();
    Folders& fold = Folders::GetInstance();
    size_t numfoldersbefore = fold.GetCount();

    files.AddFile(dirname, fname, "", "", 0);
    files.AddFile(dirname, fname, "", "", 0);
    size_t countafter = files.GetCount();
    size_t numfoldersafter = fold.GetCount();

    ASSERT_EQ(1, countafter - countbefore);
    ASSERT_EQ(1, numfoldersafter - numfoldersbefore);

    countbefore = countafter;
    numfoldersbefore = numfoldersafter;
    fname = "readme2.txt";
    files.AddFile(dirname, fname, "", "", 0);
    countafter = files.GetCount();
    numfoldersafter = fold.GetCount();

    ASSERT_EQ(1, countafter - countbefore);
    ASSERT_EQ(0, numfoldersafter - numfoldersbefore);

}


TEST(Misc, AddFolderTwice)
{
    string dirname = "c:\\windows2";

    Folders& fold = Folders::GetInstance();
    size_t numfoldersbefore = fold.GetCount();

    fold.AddFolder(dirname, "", 0);				// TO DO: add support for folder category	
    fold.AddFolder(dirname, "", 0);
    size_t numfoldersafter = fold.GetCount();

    ASSERT_EQ(1, numfoldersafter - numfoldersbefore);
}


TEST(Misc, FullPathCreation)
{
    string folderpath = "C:\\Windows\\";
    string filepath = "myfile.txt";

    std::string foldername = fs::path(folderpath).parent_path().string();
    std::string filename = fs::path(filepath).filename().string();
    fs::path absolutePath = fs::path(folderpath) / fs::path(filepath);
    string fullpath = absolutePath.string();
    ASSERT_EQ(fullpath, "C:\\Windows\\myfile.txt");
}


TEST(Misc, TupleSearch)
{
    list<Category> categoryList;
	list<tuple<string, string>> categoryExtensions;             // extension, category name
	list<tuple<string, string>> categoryPaths;                  // fullpath, category name

    Categories& categories = Categories::GetInstance();
    categories.Load();
    categoryList = categories.GetCategories();

    // below should be done every hour
    for (list<Category>::const_iterator it = categoryList.begin(); it != categoryList.end(); ++it)
    {
        Category c = *it;
        stringstream ss(c.GetExtensions());
        std::vector<std::string> tokens;
        string temp;
        char del = ',';
        std::tuple<string, string> t;
        while (getline(ss, temp, del)) {
            t = std::make_tuple(temp, c.GetName());         // extension - category name
            categoryExtensions.push_back(t);
        }

        stringstream ss1(c.GetFolderLocations());
        tokens.clear();
        while (getline(ss1, temp, del)) {
            if (!temp.empty())
            {
                t = std::make_tuple(temp, c.GetName());     // fullpath - category name
                categoryPaths.push_back(t);
            }
        }
    }

    string fileextension = "txt";
    tuple<string, string> extCatname = make_tuple(fileextension, "");
    auto ss = find_if(categoryExtensions.begin(), categoryExtensions.end(),
        [extCatname](tuple<string, string> t) -> bool {
            if (get<0>(t) == get<0>(extCatname)) {
                return true;
            }
            return false;
        });

    if (ss != std::end(categoryExtensions))
    {
        ASSERT_EQ("Documents", get<1>(*ss));
    }
    else
    {
        FAIL();
    }
}


