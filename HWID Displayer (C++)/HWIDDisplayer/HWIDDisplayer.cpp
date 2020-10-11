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
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")

using namespace std;
string GetHWID();

int main()
{
	std::cout << GetHWID();
	string Stop;
	std::cin >> Stop;
}

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