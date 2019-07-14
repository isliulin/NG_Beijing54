#pragma once
#include "ExportDll.h"
#ifndef NULL
#define NULL 0
#endif
class NGSTRING_API NGString
{
protected:
	char * p_str;
	size_t csize;
public:
	NGString();
	NGString(const NGString & str);
	NGString(const char * c_str);
	NGString(const char* p_start,const char * p_end);
	NGString(const char * c_str,size_t);
	~NGString();
public:
	NGString& operator = (const NGString & str);
	NGString& operator = (const char* c_str);
	NGString& operator += (const NGString &str);
	NGString& operator += (const char* c_str);
	NGString& operator += (const char c);
	NGString operator+ (const NGString & str);
	NGString operator+ (const char* c_str);
	operator const char*()const {return p_str?p_str:"";}
	bool operator == (const char * c_str);
	bool operator != (const char * c_str);
	bool operator == (const NGString & str);
	bool operator != (const NGString & str);
	char operator [](int i) const;

	friend NGSTRING_API NGString operator+ (const char * c_str,const NGString & str);
public:
	const char * c_str() const;
	bool empty() const;
	size_t size() const;
	void clear();
public:

	void append(const char * c_str,size_t len);
	void append(const NGString& c_str,size_t start,size_t len);
	NGString substr(size_t offset,size_t len) const;
	int find(const char c,size_t startindex = 0) const;
	int refind(const char c) const;	
	int find(const char * c_str,size_t startindex =0) const;
	int find(NGString & c_str,size_t startindex=0) const;
	int findignorecase(const char* c_str,size_t startindex=0) const;
	int findignorecase(NGString & c_str,size_t startindex=0) const;

	void replace(const char new_c,const char old_c,size_t startindex = 0);
	void replace(const char * newstr,const char *oldstr);
	int compare(const char* c_str);
public:
	void toUpper();
	void toLower();
	void trimLeft();
	void trimRight();
	void trim();
};


template <class T>
class NGSTRING_TEMPLATE NGVectorItem
{
public:
	T mNode;
	NGVectorItem *pNext;
public:
	NGVectorItem(T & val)
	{
		mNode = val;
		pNext = NULL;
	}

};

template <class T>
class NGSTRING_TEMPLATE NGVector
{
protected:
	int mSize;
	NGVectorItem<T> * pNGVector;
	NGVectorItem<T> * pCurNGVector;
	NGVectorItem<T> * pTail;
	int mCurrentInd;
public:
	NGVector()
	{
		mCurrentInd = -1;
		mSize = 0;
		pNGVector = NULL;
		pCurNGVector = NULL;
		pTail = NULL;
	}

	NGVector<T>(const NGVector<T>& ngver)
	{
		mCurrentInd = -1;
		mSize = 0;
		pNGVector = NULL;
		pCurNGVector = NULL;
		pTail = NULL;
		NGVectorItem<T> *pTemp = ngver.pNGVector;
		while(pTemp)
		{
			push_back(pTemp->mNode);
			pTemp = pTemp->pNext;
		}		
	}

	~NGVector()
	{
		clear();
	}
	void clear()
	{
		NGVectorItem<T> *pTemp = pNGVector;
		while(pTemp!=NULL)
		{
			pNGVector = pTemp->pNext;
			delete pTemp;
			pTemp = pNGVector;
		}
		pNGVector = NULL;
		pCurNGVector = NULL;
		pTail = NULL;
		mSize = 0;
		mCurrentInd = -1;
	}

	void push_back(T & val)
	{
		NGVectorItem<T> *newNode = new NGVectorItem<T>(val);
		if(pNGVector==NULL)
		{
			pNGVector = newNode;
			pCurNGVector = pNGVector;
			mCurrentInd = 0;
		}
		if(pTail!=NULL)
			pTail->pNext = newNode;
		pTail = newNode;
		//
		mSize ++ ;
	}

	int size() const {return mSize;}

	T& operator [](int i)
	{
		static T node ; // 越界处理
		if(i<mCurrentInd)
		{
			mCurrentInd = 0;
			pCurNGVector = pNGVector;
		}
		//
		while(pCurNGVector&&(mCurrentInd<i))
		{
			pCurNGVector = pCurNGVector->pNext;
			mCurrentInd ++;
		}

		return pCurNGVector?pCurNGVector->mNode:node;
	}


	NGVector<T>& operator = (const NGVector<T> & ngver)
	{
		if(this == &ngver)
			return *this;
		//
		clear();

		NGVectorItem<T> *pTemp = ngver.pNGVector;
		while(pTemp)
		{
			push_back(pTemp->mNode);
			pTemp = pTemp->pNext;
		}		
		return *this;
	}

};


