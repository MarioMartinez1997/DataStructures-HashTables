#pragma once
#include <iostream>
#include <Windows.h>
#include "SLList.h"

template<typename Type>

class HTable
{
	
	SLList<Type>* lArray;
	unsigned int(*FuncionA) (const Type&);
	int Size;
	
public:
	
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor 
	// Parameters : numOfBuckets - the number of buckets
	//              hFunction - pointer to the hash function for this table
	// Notes : constructs an empty hash table
	/////////////////////////////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		lArray = new SLList<Type>[numOfBuckets];
		FuncionA = hFunction;
		Size = numOfBuckets;
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : destroys a hash table
		/////////////////////////////////////////////////////////////////////////////
	~HTable()
	{
		clear();
		delete[] lArray;
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		/////////////////////////////////////////////////////////////////////////////
	HTable<Type>& operator=(const HTable<Type>& that) 
	{
		delete[] lArray;
		lArray = new SLList<Type>[that.Size];

		Size = that.Size;
		for (int i = 0; i < Size; i++)
		{
			lArray[i] = that.lArray[i];
		}
		FuncionA = that.FuncionA;
		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	HTable(const HTable<Type>& that) 
	{

		*this = that;
	}


		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters : v - the item to insert into the hash table
		/////////////////////////////////////////////////////////////////////////////
	void insert(const Type& v) 
	{
		lArray[FuncionA(v)].addHead(v);		
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : findAndRemove
		// Parameters : v - the item to remove(if it is found)
		/////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const Type& v)
	{
		unsigned int index = FuncionA(v);
		SLLIter<Type> iter(lArray[index]);
		iter.begin();
		while (!iter.end())
		{
			if (iter.current() == v)
			{
				lArray[index].remove(iter);
				return true;
			}
			else
			{
				++iter;
			}
		}
		return false;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the hash table
		/////////////////////////////////////////////////////////////////////////////
	void clear() 
	{
		for (int i = 0; i < Size ; i++)
		{
			lArray[i].clear();
		}
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : find
		// Parameters : v - the item to look for
		// Return : the bucket we found the item in or -1 if we didn’t find the item.
		/////////////////////////////////////////////////////////////////////////////
	int find(const Type& v) const 
	{
		int ret = -1;
		unsigned int index = FuncionA(v);
		SLLIter<Type> iter(lArray[index]);
		iter.begin();

		for (int i = 0; i < lArray[index].size(); i++)
		{
			if (iter.current() == v)
			{
				ret = index;
				
			}
			else
			{
				++iter;
			}
		}
		return ret;
	}

};

