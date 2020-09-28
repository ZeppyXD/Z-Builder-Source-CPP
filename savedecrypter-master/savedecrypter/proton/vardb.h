//  ***************************************************************
//  SharedDB - Creation date: 04/11/2009
//  -------------------------------------------------------------
//  Robinson Technologies Copyright (C) 2009 - All Rights Reserved
//
//  ***************************************************************
//  Programmer(s):  Seth A. Robinson (seth@rtsoft.com)
//  ***************************************************************
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#ifndef VariantDB_h__
#define VariantDB_h__
#include "Variant.hpp"
#include <hash_map>

//modified so msvc2015 will compile, from hisadg123 
#if _MSC_VER >= 1700
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#endif
class Variant;
typedef stdext::hash_map<string, Variant*> dataList;
using namespace std;
class VariantDB
{
public:
	VariantDB();
	virtual ~VariantDB();


	Variant* GetVar(const string& keyName);  //created it needed, this is usually what you want
	Variant* GetVarIfExists(const string& keyName);  //returns null if not created yet
	Variant* GetVarWithDefault(const string& keyName, const Variant& vDefault);

	bool Load(const string& fileName, bool* pFileExistedOut = NULL, bool bAddBasePath = true);

	string DumpAsString();
	void DeleteAll();
	int GetVarCount() { return (int)m_data.size(); }

	void Clear();
	//to get each var in our db manually, do this:
	void ResetNext(); //call before starting a search
	Variant* GetNext(string& keyOut); //call this in a loop until it returns NULL to signal the finish, callResetNext() before using!

	VariantDB& operator= (const VariantDB& rhs)
	{
		//m_functionData = rhs.m_functionData;
		dataList::const_iterator itor = rhs.m_data.begin();

		while (itor != rhs.m_data.end())
		{
			m_data[itor->first] = new Variant(*itor->second);
			itor++;
		}
		return *this;
	}

	VariantDB(const VariantDB& ref)
	{
		*this = ref;
	}

private:

	dataList m_data;
	dataList::iterator m_nextItor;
};

#endif // Variant_h__
