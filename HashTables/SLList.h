#pragma once
#include <iostream>
#include <Windows.h>


template<typename Type> class SLLIter;

template<typename Type>
class SLList
{
	friend class SLLIter<Type>;

	struct Node
	{
		Type element;
		Node* Next = nullptr;
	};

	Node* Head;
	int Size =0;

	void pCopy(const Node * n)
	{
		if (n != nullptr)
		{
			pCopy(n->Next);
			addHead(n->element);
		}	
	}
public:

	SLList()
	{
		Head = nullptr;
		Size = 0;
	}
	~SLList()
	{
		clear();
	}
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		if (this != &that)
		{
			clear();
			pCopy(that.Head);
		}		

		return *this;

	}
	SLList(const SLList<Type>& that)
	{

		Head = nullptr;
		Size = 0;
		*this = that;		

	}
	void addHead(const Type& input)
	{
		Node* bob = new Node;
		bob->element = input;
		bob->Next = Head;
		Head = bob;
		Size++;
	
	}
	//void addHead(const type &input)

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		while (Head != nullptr)
		{
			
			Node* n = Head;
			Head = Head->Next;
			delete n;
		}
		Size = 0;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :	index - an iterator to the location to insert at
	//				v - the item to insert
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& input)
	{
		if (index.c != nullptr)
		{
			if (index.c != Head)
			{

				Node* temp = new Node();

				temp->element = input;
				index.pc->Next = temp;
				temp->Next = index.c;
				index.c = temp;
				Size++;
			}
			else
			{
				addHead(input);
				index.c = Head;
			}
		}
		return;

	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : remove
	// Parameters :	index - an iterator to the location to remove from
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index)
	{
		if (index.c != nullptr)
		{
			if (index.c != Head)
			{
				index.pc->Next = index.c->Next;
				delete index.c;
				index.c = index.pc->Next;
			}
			else
			{
				Head = Head->Next;
				delete index.c;
				index.c = Head;
			}
			
			Size--;
		}
		return;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : size
	// Return : the number of items stored in the linked list.
	/////////////////////////////////////////////////////////////////////////////
	unsigned int size() const { return Size; }
};

template<typename Type>
class SLLIter
{
	friend class SLList<Type>;
	typename SLList<Type>::Node * c;
	typename SLList<Type>::Node * pc;
	SLList<Type> *Test;

public:
		/////////////////////////////////////////////////////////////////////////////
		// Function : Constructor
		// Parameters :	listToIterate - the list to iterate
		/////////////////////////////////////////////////////////////////////////////
		SLLIter(SLList<Type>& listToIterate) 
	{
		Test = &listToIterate;
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : begin
		// Notes : moves the iterator to the head of the list
		/////////////////////////////////////////////////////////////////////////////
	void begin() 
	{
		c = Test->Head;
		pc = nullptr;
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : end
		// Notes : returns true if we are at the end of the list, false otherwise
		/////////////////////////////////////////////////////////////////////////////
	bool end() const
	{
		// (c != nullptr) {
			if (c == nullptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		
	}
		/////////////////////////////////////////////////////////////////////////////
		// Function : operator++
		// Notes : move the iterator forward one node
		/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++()
	{
		if (c != nullptr)
		{
			pc = c;
			c = c->Next;
		}
		return *this;
	}

		/////////////////////////////////////////////////////////////////////////////
		// Function : current
		// Notes : returns the item at the current iterator location
		/////////////////////////////////////////////////////////////////////////////
	Type& current() const
	{
		return c->element;
	}

};


	//The SLLIter class will have the following public interface :


