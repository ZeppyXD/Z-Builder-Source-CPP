#pragma once
#ifndef __REGISTRY_REIJI_
#define __REGISTRY_REIJI_

#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <wincrypt.h>

#pragma comment(lib, "Crypt32.lib")

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

bool NaN(std::wstring text) {
	for (int i = 0; i < (int)text.length(); i++) if (text[i] < 48 || text[i] > 57) return true;
	return false;
}

std::wstring FindKey(HKEY hKey, std::wstring value, bool keys = false) {

	TCHAR    achKey[MAX_KEY_LENGTH];
	DWORD    cbName;
	TCHAR    achClass[MAX_PATH] = TEXT("");
	DWORD    cchClassName = MAX_PATH;
	DWORD    cSubKeys = 0;
	DWORD    cbMaxSubKey;
	DWORD    cchMaxClass;
	DWORD    cValues;
	DWORD    cchMaxValue;
	DWORD    cbMaxValueData;
	DWORD    cbSecurityDescriptor;
	FILETIME ftLastWriteTime;

	DWORD _i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;
	retCode = RegQueryInfoKey(hKey, achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey, &cchMaxClass, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);

	if (keys && cSubKeys) {
		for (_i = 0; _i < cSubKeys; _i++) {
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, _i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS && ((value.length() && std::wstring(achKey).find(value) != std::string::npos) || (!value.length() && !NaN(achKey)))) return std::wstring(achKey);
			//if (retCode == ERROR_SUCCESS && std::wstring(achKey).find(value) != std::string::npos) return achKey;
		}
	}
	if (!keys && cValues) {
		for (_i = 0, retCode = ERROR_SUCCESS; _i < cValues; _i++) {
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValue(hKey, _i, achValue, &cchValue, NULL, NULL, NULL, NULL);
			if (retCode == ERROR_SUCCESS && std::wstring(achValue).find(value) != std::string::npos) return (std::wstring)achValue;
			//if (retCode == ERROR_SUCCESS && std::wstring(achValue).find(value) != std::string::npos) std::wstring(achValue);
		}
	}
	return L"";
}

std::vector<std::wstring> FindKeyAll(HKEY hKey, std::wstring subkey, bool keys = false) {

	TCHAR    achKey[MAX_KEY_LENGTH];
	DWORD    cbName;
	TCHAR    achClass[MAX_PATH] = TEXT("");
	DWORD    cchClassName = MAX_PATH;
	DWORD    cSubKeys = 0;
	DWORD    cbMaxSubKey;
	DWORD    cchMaxClass;
	DWORD    cValues;
	DWORD    cchMaxValue;
	DWORD    cbMaxValueData;
	DWORD    cbSecurityDescriptor;
	FILETIME ftLastWriteTime;

	DWORD _i, retCode;

	TCHAR  achValue[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;
	HKEY HK;
	if (RegOpenKeyEx(hKey, subkey.c_str(), 0, KEY_READ | KEY_WOW64_32KEY, &HK) != ERROR_SUCCESS) {
		if (RegOpenKeyEx(hKey, subkey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &HK) != ERROR_SUCCESS) {
			return {};
		}
	}
	retCode = RegQueryInfoKey(HK, achClass, &cchClassName, NULL, &cSubKeys, &cbMaxSubKey, &cchMaxClass, &cValues, &cchMaxValue, &cbMaxValueData, &cbSecurityDescriptor, &ftLastWriteTime);
	std::vector<std::wstring> result;
	if (keys && cSubKeys) {
		for (_i = 0; _i < cSubKeys; _i++) {
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(HK, _i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
			if (retCode == ERROR_SUCCESS) result.push_back(achKey);
			//if (retCode == ERROR_SUCCESS && std::wstring(achKey).find(value) != std::string::npos) return achKey;
		}
	}
	if (!keys && cValues) {
		for (_i = 0, retCode = ERROR_SUCCESS; _i < cValues; _i++) {
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';
			retCode = RegEnumValue(HK, _i, achValue, &cchValue, NULL, NULL, NULL, NULL);
			if (retCode == ERROR_SUCCESS) result.push_back(achValue);
			//if (retCode == ERROR_SUCCESS && std::wstring(achValue).find(value) != std::string::npos) std::wstring(achValue);
		}
	}
	RegCloseKey(HK);
	return result;
}


bool RegKeyExists(HKEY hKey, std::wstring key) {
	HKEY HK = NULL;
	if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_READ | KEY_WOW64_32KEY, &HK) != ERROR_SUCCESS) {
		if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &HK) != ERROR_SUCCESS) {
			return false;
		}
		else RegCloseKey(HK);
	}
	else RegCloseKey(HK);
	return true;
}

bool RegKeyGetValueBinary(HKEY hKey, std::wstring key, std::wstring value, std::wstring& _32bit, std::wstring& _64bit, std::wstring& devaultValue) {
	HKEY HK = NULL;
	bool oneget = false;

	BYTE dwBuffer[501];
	DWORD dwType = REG_BINARY, dwSize = 500;

	int flags[2] = { KEY_WOW64_32KEY, KEY_WOW64_64KEY };
	std::wstring* values[2] = { &_32bit, &_64bit };

	for (int i = 0; i < 2; i++) {
		if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_READ | flags[i], &HK) == ERROR_SUCCESS) {
			DWORD error = RegQueryValueEx(HK, value.c_str(), 0, &dwType, dwBuffer, &dwSize);
			if (error == ERROR_SUCCESS) {
				std::wstring buf = L"";
				for (unsigned int i = 0; i < dwSize; i++) {
					std::wstringstream wstream;
					wstream << std::hex << dwBuffer[i];
					std::wstring res(wstream.str());
					if (res.length() == 1) res = L"0" + res;
					buf += res;
				}
				*values[i] = buf;
				if (!oneget) devaultValue = buf;
				oneget = true;
			}
			RegCloseKey(HK);
		}
	}
	return oneget;
}

bool RegKeySetValueBinary(HKEY hKey, std::wstring key, std::wstring value, std::string content) {
	DWORD BinLength = content.length() / 2;
	BYTE* Bin = new BYTE[BinLength];
	CryptStringToBinaryA(content.c_str(), content.length(), CRYPT_STRING_HEX, Bin, &BinLength, NULL, NULL);

	bool setter = false;
	HKEY HK = NULL;
	if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_WRITE | KEY_WOW64_32KEY, &HK) == ERROR_SUCCESS) {
		if (RegSetValueEx(HK, value.c_str(), 0, REG_BINARY, Bin, BinLength) == ERROR_SUCCESS) {
			setter = true;
		}
		RegCloseKey(HK);
	}

	if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_WRITE | KEY_WOW64_64KEY, &HK) == ERROR_SUCCESS) {
		if (RegSetValueEx(HK, value.c_str(), 0, REG_BINARY, Bin, BinLength) == ERROR_SUCCESS) {
			setter = true;
		}
		RegCloseKey(HK);
	}

	return setter;
}

bool RegKeyGetValueRegSz(HKEY hKey, std::wstring key, std::wstring value, std::wstring& _32bit, std::wstring& _64bit, std::wstring& devaultValue) {
	HKEY HK = NULL;

	wchar_t szBuffer[1001];
	DWORD dwBufferSize = 1000;
	DWORD dwType = REG_SZ;

	int flags[2] = { KEY_WOW64_32KEY, KEY_WOW64_64KEY };
	std::wstring* values[2] = { &_32bit, &_64bit };

	bool oneget = false;

	for (int i = 1; i >= 0; i--) {
		if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_READ | flags[i], &HK) == ERROR_SUCCESS) {
			if (RegQueryValueEx(HK, value.c_str(), 0, &dwType, (LPBYTE)szBuffer, &dwBufferSize) == ERROR_SUCCESS) {
				*values[i] = std::wstring(szBuffer);
				if (!oneget) devaultValue = std::wstring(szBuffer);
				oneget = true;
			}
			RegCloseKey(HK);
		}
	}
	return oneget;
}

bool RegKeySetValueRegSz(HKEY hKey, std::wstring key, std::wstring value, std::wstring content) {
	bool setter = false;
	HKEY HK = NULL;
	if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_WRITE | KEY_WOW64_32KEY, &HK) == ERROR_SUCCESS) {
		if (RegSetValueEx(HK, value.c_str(), 0, REG_SZ, (const BYTE*)content.c_str(), content.size() * 2) == ERROR_SUCCESS) setter = true;
		RegCloseKey(HK);
	}

	if (RegOpenKeyEx(hKey, key.c_str(), 0, KEY_WRITE | KEY_WOW64_64KEY, &HK) == ERROR_SUCCESS) {
		if (RegSetValueEx(HK, value.c_str(), 0, REG_SZ, (const BYTE*)content.c_str(), content.size() * 2) == ERROR_SUCCESS) setter = true;
		RegCloseKey(HK);
	}
	return setter;
}

#endif
