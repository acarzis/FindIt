#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#include <boost/filesystem.hpp>
#include "DriveOperations.h"

#include <stdio.h>
#define _WIN32_DCOM
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <comdef.h>
#include "Registry.h"

using namespace std;
namespace fs = boost::filesystem;

void DriveOperations::EnumerateFolders(std::string fullpath, std::list<std::string>& folderlist)
{
    try
    {
        fs::path p(fullpath);
        fs::directory_iterator end_itr;
        for (fs::directory_iterator itr(p); itr != end_itr; ++itr)      // top level only, not recursive
        {
            if (is_directory(itr->path()))
            {
                folderlist.push_back(itr->path().string());
            }
        }
    }
    catch (exception& e)
    {
    }
}

void DriveOperations::EnumerateFiles(string fullpath, list<string>& filelist)
{
    try
    {
        fs::path p(fullpath);
        fs::directory_iterator end_itr;
        for (fs::directory_iterator itr(p); itr != end_itr; ++itr)      // top level only, not recursive
        {
            if (!is_directory(itr->path()))
            {
                filelist.push_back(itr->path().string());
            }
        }
    }
    catch (exception& e)
    {
    }
}

uintmax_t DriveOperations::Filesize(string fullpath)
{
    try
    {
        fs::path p(fullpath);
        if (is_regular_file(p))
        {
            return fs::file_size(p);
        }
    }
    catch (exception& e)
    {
    }
    return 0;
}

DateTime DriveOperations::GetLastWriteTime(string foldername)
{
    DateTime result;

    try
    {
        fs::path directoryinfo(foldername);
        if (fs::is_directory(directoryinfo))
        {
            result = DateTime(fs::last_write_time(directoryinfo));
        }
    }

    catch (exception& e)
    {
    }
    return result;
}


//https://stackoverflow.com/questions/286534/enumerating-all-available-drive-letters-in-windows
std::vector<std::string> DriveOperations::getListOfDrives() {
    std::vector<std::string> arrayOfDrives;
    char* szDrives = new char[MAX_PATH]();
    if (GetLogicalDriveStringsA(MAX_PATH, szDrives));
    for (int i = 0; i < 100; i += 4)
        if (szDrives[i] != (char)0)
            arrayOfDrives.push_back(std::string{ szDrives[i],szDrives[i + 1],szDrives[i + 2] });
    delete[] szDrives;
    return arrayOfDrives;
}


// https://stackoverflow.com/questions/62906482/how-do-i-determine-a-mapped-drives-details
void DriveOperations::PrintDriveDetails(wstring drive)
{
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    HRESULT hr;

    IWbemLocator* pWbemLocator = NULL;
    IWbemServices* pServices = NULL;
    IWbemClassObject* pDrive = NULL;
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL, EOAC_NONE, 0);

    if (FAILED(hr))
    {
        CoUninitialize();
        cout << "Failed to initialize security. Error code = 0x" << hex << hr << endl;
        return;
    }

    hr = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (void**)&pWbemLocator);
    if (FAILED(hr))
    {
        CoUninitialize();
        cout << "Failed to CoCreateInstance. Error code = 0x" << hex << hr << endl;
        return;
    }

    _bstr_t bstrNamespace = L"root\\cimv2";

    hr = pWbemLocator->ConnectServer(bstrNamespace, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
    if (FAILED(hr))
    {
        pWbemLocator->Release();
        CoUninitialize();
        cout << "Failed to Connect to the Server. Error code = 0x" << hex << hr << endl;
        return;
    }
    pWbemLocator->Release();
    printf("Successfully connected to namespace.\n");

    hr = CoSetProxyBlanket(
        pServices,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );
    if (FAILED(hr))
    {
        pServices->Release();
        cout << "Could not set proxy blanket. Error code = 0x" << hex << hr << endl;
        CoUninitialize();
        return;               // Program has failed.
    }

    wstring bstrPath = L"Win32_LogicalDisk.DeviceID=\"" + drive + L"\"";

    // 
    // Perform a full-instance retrieval. 
    // 
    hr = pServices->GetObject(BSTR(bstrPath.c_str()),
        0, 0, &pDrive, 0);
    if (FAILED(hr))
    {
        pServices->Release();
        CoUninitialize();
        cout << "failed GetObject. Error code = 0x" << hex << hr << endl;
        return;
    }

    // Display the object
    BSTR  bstrDriveObj;
    hr = pDrive->GetObjectText(0, &bstrDriveObj);
    if (FAILED(hr))
    {
        pServices->Release();
        CoUninitialize();
        cout << "failed GetObjectText. Error code = 0x" << hex << hr << endl;
        return;
    }
    printf("%S\n\n", bstrDriveObj);

    VARIANT freesize, totalsize;
    hr = pDrive->Get(L"FreeSpace", 0, &freesize, 0, NULL);
    if (FAILED(hr))
    {
        pServices->Release();
        CoUninitialize();
        cout << "failed Get FreeSpace. Error code = 0x" << hex << hr << endl;
        return;
    }
    printf("free space: %S\n", freesize.bstrVal);

    hr = pDrive->Get(L"Size", 0, &totalsize, 0, NULL);
    if (FAILED(hr))
    {
        pServices->Release();
        CoUninitialize();
        cout << "failed Get Size. Error code = 0x" << hex << hr << endl;
        return;
    }
    printf("total size: %S\n", totalsize.bstrVal);

    VariantClear(&freesize);
    VariantClear(&totalsize);
    pDrive->Release();
    pServices->Release();
    pServices = NULL;

    CoUninitialize();
}



// as per :  https://stackoverflow.com/questions/2067075/how-do-i-determine-a-mapped-drives-actual-path
std::wstring DriveOperations::UNCPathW(std::string path)
{
    HKEY hKey;
    wstring pathws(path.begin(), path.end());
    wstring subkey(L"Network\\");
    subkey += path[0];
    
    LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER, subkey.c_str(), 0, KEY_READ, &hKey);
    
    if (lRes != ERROR_SUCCESS)
    {
        if (lRes == ERROR_FILE_NOT_FOUND) {
            printf("Key not found.\n");
            return L"";
        }
        else {
            printf("Error opening key.\n");
            return L"";
        }
    }

    bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
    bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);
    std::wstring strKeyDefaultValue = pathws;

    if (wcsncmp(pathws.c_str(), L"\\\\", 1))
    {
        GetStringRegKeyW(hKey, L"RemotePath", strKeyDefaultValue, L"bad");
    }

    return strKeyDefaultValue;
}

std::string DriveOperations::UNCPath(std::string path)
{
    HKEY hKey;
    string subkey("Network\\");
    subkey += path[0];

    LONG lRes = RegOpenKeyEx(HKEY_CURRENT_USER, subkey.c_str(), 0, KEY_READ, &hKey);

    if (lRes != ERROR_SUCCESS)
    {
        if (lRes == ERROR_FILE_NOT_FOUND) {
            printf("Key not found.\n");
            return "";
        }
        else {
            printf("Error opening key.\n");
            return "";
        }
    }

    bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
    bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);
    std::string strKeyDefaultValue = path;

    if (strncmp(path.c_str(), "\\\\", 1))
    {
        GetStringRegKey(hKey, "RemotePath", strKeyDefaultValue, "bad");
    }

    return strKeyDefaultValue;
}
