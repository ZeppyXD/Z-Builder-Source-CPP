#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "vardb.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)      { if(p) { delete (p); (p)=NULL; } }
#endif
VariantDB::VariantDB()
{
	ResetNext();
}

VariantDB::~VariantDB()
{
	DeleteAll();
}
string GetSavePath()
{
	return "";
}
void VariantDB::DeleteAll()
{
	dataList::iterator itor = m_data.begin();
	while (itor != m_data.end())
	{
		SAFE_DELETE(itor->second);
		itor++;
	}

	m_data.clear();
}

bool LoadFromFile(string& str, FILE* fp)
{
	int size;
	fread(&size, sizeof(int), 1, fp);
	if (size > 0)
	{
		str.resize(size, ' ');
		fread(&str[0], size, 1, fp);
	}
	else
		str.clear();	
	return true;
}

Variant* VariantDB::GetVarIfExists(const string& keyName)
{
	dataList::iterator itor = m_data.find(keyName);

	if (itor != m_data.end())
	{
		//bingo!
		return &((*itor->second));
	}

	return NULL;
}



Variant* VariantDB::GetVarWithDefault(const string& keyName, const Variant& vDefault)
{

	Variant* pData = GetVarIfExists(keyName);

	if (!pData)
	{
		//create it
		pData = new Variant(vDefault);
		m_data[keyName] = pData;
	}

	return pData;
}

Variant* VariantDB::GetVar(const string& keyName)
{

	Variant* pData = GetVarIfExists(keyName);

	if (!pData)
	{
		//create it
		pData = new Variant;
		m_data[keyName] = pData;
	}

	return pData;
}

bool LoadFromFile(int32& num, FILE* fp)
{
	fread(&num, sizeof(int32), 1, fp);
	return true;
}

bool LoadFromFile(float& num, FILE* fp)
{
	fread(&num, sizeof(float), 1, fp);
	return true;
}

bool LoadFromFile(bool& num, FILE* fp)
{
	fread(&num, sizeof(bool), 1, fp);
	return true;
}
bool LoadFromFile(uint32& num, FILE* fp)
{
	fread(&num, sizeof(uint32), 1, fp);
	return true;
}
bool LoadFromFile(CL_Vec2f& num, FILE* fp)
{
	fread(&num, sizeof(CL_Vec2f), 1, fp);
	return true;
}

bool LoadFromFile(CL_Vec3f& num, FILE* fp)
{
	fread(&num, sizeof(CL_Vec3f), 1, fp);
	return true;
}

bool LoadFromFile(CL_Rectf& num, FILE* fp)
{
	fread(&num, sizeof(CL_Rectf), 1, fp);
	return true;
}
void RemoveFile(string fileName, bool bAddSavePath)
{
	int ret;

	if (bAddSavePath)
	{
		ret = _unlink((GetSavePath() + fileName).c_str());
	}
	else
	{
		ret = _unlink((fileName).c_str());
	}
}
bool VariantDB::Load(const string& fileName, bool* pFileExistedOut, bool bAddBasePath)
{
	string f;

	if (bAddBasePath)	
		f = GetSavePath() + fileName;
	else
		f = fileName;
	

	FILE* fp = fopen(f.c_str(), "rb");

	if (!fp)
	{
		if (pFileExistedOut)* pFileExistedOut = false;
		return false; 
	}

	//get the version
	uint32 version;
	if (pFileExistedOut)* pFileExistedOut = true;
	size_t bytesRead = fread(&version, 1, sizeof(uint32), fp);

	if (bytesRead == 0 || version != 1)
	{
		fclose(fp);
		RemoveFile(f, false);
		return false;
	}

	string s;
	uint32 varType;

	while (!feof(fp))
	{
		fread(&varType, 1, sizeof(uint32), fp);

		if (varType == Variant::type_a)
		{
			//out signal that we're done reading this part
			break;
		}

		//get the var name
		LoadFromFile(s, fp);

#ifdef _DEBUG
		if (GetVarIfExists(s) != NULL) {
			//LogMsg("VariantDB: variable %s already exists in database while loading from file %s. The previous value gets overwritten!", s.c_str(), fileName.c_str());
		}
#endif

		//get the actual data too
		switch (varType)
		{

		case Variant::type_c:
		{
			string v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		case Variant::type_f:
		{
			uint32 v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		case Variant::type_z:
		{
			int32 v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		case Variant::type_b:
		{
			float v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		case Variant::type_d:
		{
			CL_Vec2f v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		case Variant::type_e:
		{
			CL_Vec3f v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		case Variant::type_y:
		{
			CL_Rectf v;
			LoadFromFile(v, fp);
			GetVar(s)->Set(v);
			break;
		}

		default:
			fclose(fp);
			return false;
		}


	}
	fclose(fp);
	return true;

}


std::string VariantDB::DumpAsString()
{
	string log = "*********************\r\n";

	dataList::iterator itor = m_data.begin();

	while (itor != m_data.end())
	{
		Variant* pV = itor->second;
		string s = itor->first + ": " + pV->Print();

		log += s + "\n";
		itor++;
	}

	log += "\r\n";
	return log;
}

void VariantDB::ResetNext()
{
	m_nextItor = m_data.begin();
}

Variant* VariantDB::GetNext(string& keyOut)
{
	Variant* pReturn = NULL;

	if (m_nextItor == m_data.end())
	{
		//all done
		ResetNext();
		return NULL;
	}

	keyOut = m_nextItor->first;
	pReturn = m_nextItor->second;
	m_nextItor++;
	return pReturn;
}
bool StringFromStartMatches(const std::string& line, const std::string textToMatch)
{
	for (uint32 i = 0; i < textToMatch.size(); i++)
	{
		if (i >= line.length()) return false;
		if (line[i] != textToMatch[i]) return false;
	}
	return true;
}

void VariantDB::Clear()
{
	m_data.clear();
	ResetNext();
}