#ifndef LIST_H

#define LIST_H

// Header Files

#include <iostream>
#include <iomanip>

// Class Declarations

using namespace std;

template<typename T>
int MyMain(T);

template <typename T>
class NODE
{
	NODE<T>* pPrev;
	T		 t_Data;
	NODE<T>* pNext;

public:

	// Functions Declarations

	NODE();
	~NODE();

	template <typename T>
	friend class LIST;
};

template <typename T>
class LIST
{
	NODE<T>* pDummy;

public:

	// Function Declarations

	LIST();
	~LIST();

	void InsertFirst(T);
	void InsertLast(T);
	void InsertAtPosition(int, T);

	T DeleteFirst();
	T DeleteLast();
	T DeleteAtPosition(int);

	int SearchFirstOccurance(T);
	int SearchLastOccurance(T);
	int SearchAllOccurances(T);

	void Display();
	bool IsEmpty();
	void DeleteAll();
	int	 CountNode();

	class Iterator
	{
		NODE<T>* pCurrentNode;

	public:

		Iterator();
		~Iterator();

		// Function Declarations

		NODE<T>* GetCurrentNode();
		void  SetCurrentNode(NODE<T>*);

		// Overloaded Operator Declarations

		int		 operator *();

		bool	 operator !=(const Iterator&);
		bool	 operator ==(const Iterator&);
		bool	 operator <=(const Iterator&);
		bool	 operator >=(const Iterator&);

		Iterator& operator ++();
		Iterator  operator ++(int);
		Iterator& operator --();
		Iterator  operator --(int);
		LIST<T>::Iterator& operator =(NODE<T>*);

	};

	LIST::Iterator begin();
	LIST::Iterator end();

private:
	Iterator StartIter;
	Iterator EndIter;
};
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "list.h"

template <typename T>
NODE<T>::NODE()
{
	pPrev = NULL;
	t_Data = 0;
	pNext = NULL;
}

template<typename T>
NODE<T> :: ~NODE()
{
	t_Data = 0;

	if (pPrev)
		pPrev = NULL;

	if (pNext)
		pNext = NULL;
}

template<typename T>
LIST<T>::LIST()
{
	pDummy = new NODE<T>;

	if (NULL == pDummy)
	{
		cout << endl << endl << "Cannot Allocate Memory" << endl << endl;
		return;
	}

	pDummy->pPrev = NULL;
	pDummy->t_Data = 0;
	pDummy->pNext = NULL;

}

template<typename T>
LIST<T> :: ~LIST()
{
	if (pDummy)
	{
		DeleteAll();
	}

	delete(pDummy);

	pDummy = NULL;
}

template <typename T>
void LIST<T>::InsertFirst(T tData)
{
	// Local Variable

	NODE<T>* pNewNode = NULL;

	// Code

	pNewNode = new NODE<T>;

	if (NULL == pNewNode)
	{
		cout << endl << "Memory Allocation failed" << endl << endl;
		return;
	}

	pNewNode->pPrev = NULL;
	pNewNode->t_Data = tData;
	pNewNode->pNext = NULL;

	if (NULL == pDummy->pNext)
	{
		pNewNode->pNext = pDummy;
		pDummy->pPrev = pNewNode;
	}
	else
	{
		pNewNode->pNext = pDummy->pNext;
		pDummy->pNext->pPrev = pNewNode;
	}

	pNewNode->pPrev = pDummy;
	pDummy->pNext = pNewNode;
}

template <typename T>
void LIST<T>::InsertLast(T tData)
{
	// Local Variable

	NODE<T>* pNewNode = NULL;

	// Code

	pNewNode = new NODE<T>;

	if (NULL == pNewNode)
	{
		cout << endl << "Memory Allocation failed" << endl << endl;
		return;
	}

	pNewNode->pPrev = NULL;
	pNewNode->t_Data = tData;
	pNewNode->pNext = NULL;


	if (NULL == pDummy->pNext)
	{
		InsertFirst(tData);
	}
	else
	{
		pDummy->pPrev->pNext = pNewNode;
		pNewNode->pNext = pDummy;
		pNewNode->pPrev = pDummy->pPrev;
		pDummy->pPrev = pNewNode;
	}

}

template <typename T>
void LIST<T>::InsertAtPosition(int iPosition, T tData)
{
	// Local variable Declarations

	NODE<T>* pTempNode = NULL;
	NODE<T>* pNewNode = NULL;

	// Code

	if (iPosition > this->CountNode() + 1 || iPosition < 1)
	{
		cout << endl << endl << "+-+-+-+-+-+-+-+-+-+- Enter Valid Position +-+-+-+-+-+-+-+-+-+-" << endl << endl;
		return;
	}
	else if (this->IsEmpty() || 1 == iPosition)
	{
		this->InsertFirst(tData);
		return;
	}
	else if (iPosition == this->CountNode() + 1)
	{
		this->InsertLast(tData);
		return;
	}

	pNewNode = new NODE<T>;

	if (NULL == pNewNode)
	{
		cout << endl << endl << "Memory Allocation Failed" << endl << endl;
		return;
	}

	pNewNode->pPrev = NULL;
	pNewNode->iData = tData;
	pNewNode->pNext = NULL;


	pTempNode = pDummy->pNext;

	while (iPosition - 2)
	{
		pTempNode = pTempNode->pNext;
		iPosition--;
	}

	pNewNode->pNext = pTempNode->pNext;
	pNewNode->pNext->pPrev = pNewNode;
	pNewNode->pPrev = pTempNode;
	pTempNode->pNext = pNewNode;
}

template <typename T>
T LIST<T>::DeleteFirst()
{
	// Local Variable Declaration

	T tDeletedData = 0;
	NODE<T>* pTempNode = pDummy->pNext;

	// Code

	if (pDummy->pNext == pDummy->pPrev)
	{
		pDummy->pNext = NULL;
		pDummy->pPrev = NULL;
	}
	else
	{
		pDummy->pNext = pTempNode->pNext;
		pTempNode->pNext->pPrev = pDummy;
	}

	tDeletedData = pTempNode->iData;

	pTempNode->pPrev = NULL;
	pTempNode->iData = 0;
	pTempNode->pNext = NULL;

	delete(pTempNode);

	pTempNode = NULL;

	return(tDeletedData);
}

template <typename T>
T LIST<T>::DeleteLast()
{
	// Local Variable Declaration

	T tDeletedData = 0;
	NODE<T>* pTempNode = NULL;

	// Code

	if (pDummy->pNext == pDummy->pPrev)
	{
		return(tDeletedData = DeleteFirst());
	}

	pTempNode = pDummy->pPrev;

	pTempNode->pPrev->pNext = pDummy;
	pDummy->pPrev = pTempNode->pPrev;

	tDeletedData = pTempNode->iData;

	pTempNode->pPrev = NULL;
	pTempNode->iData = 0;
	pTempNode->pNext = NULL;

	delete(pTempNode);

	pTempNode = NULL;

	return(tDeletedData);
}

template <typename T>
T LIST<T>::DeleteAtPosition(int iPosition)
{
	// local Variable Declarations

	T		 tDeletedData = 0;
	NODE<T>* pTempNode = NULL;

	// Code

	if (iPosition == 1)
	{
		return(tDeletedData = DeleteFirst());
	}
	else if (iPosition == CountNode())
	{
		return(tDeletedData = DeleteLast());
	}
	else
	{
		pTempNode = pDummy->pNext;

		while (iPosition - 1)
		{
			pTempNode = pTempNode->pNext;
			iPosition--;
		}

		tDeletedData = pTempNode->iData;

		pTempNode->pPrev->pNext = pTempNode->pNext;
		pTempNode->pNext->pPrev = pTempNode->pPrev;

		delete(pTempNode);
		pTempNode = NULL;
	}

	return(tDeletedData);
}

template <typename T>
int LIST<T>::SearchFirstOccurance(T tData)
{
	// Local Variable Delcarations

	int iFoundAtPos = 1;
	NODE<T>* pTempNode = pDummy->pNext;

	// Code

	while (tData != pTempNode->iData && pTempNode != pDummy)
	{
		pTempNode = pTempNode->pNext;
		iFoundAtPos++;
	}

	if (pTempNode->iData != tData)
		return(-1);
	else
		return(iFoundAtPos);
}

template <typename T>
int LIST<T>::SearchLastOccurance(T tData)
{
	// Local Variable Delcarations

	int iFoundAtPos;
	NODE<T>* pTempNode = pDummy->pPrev;

	// Code

	iFoundAtPos = CountNode();

	while (pTempNode->iData != tData && pTempNode != pDummy)
	{
		pTempNode = pTempNode->pPrev;
		iFoundAtPos--;
	}

	if (pTempNode->iData != tData)
		return(-1);
	else
		return(iFoundAtPos);


}

template <typename T>
int LIST<T>::SearchAllOccurances(T tData)
{
	// Local Variable Delcarations

	int iFoundAtPos = 0;
	NODE<T>* pTempNode = pDummy->pNext;

	// Code

	while (pTempNode != pDummy)
	{
		if (pTempNode->iData == tData)
			iFoundAtPos++;

		pTempNode = pTempNode->pNext;
	}

	if (0 == iFoundAtPos)
		return(-1);
	else
		return(iFoundAtPos);
}

template<typename T>
void LIST<T>::DeleteAll()
{
	// Code


	if (NULL == pDummy->pNext && NULL == pDummy->pPrev)
		return;

	while (pDummy->pNext != pDummy->pPrev)
	{
		pDummy->pPrev->pPrev->pNext = pDummy->pNext;
		pDummy->pNext->pPrev = pDummy->pPrev->pPrev;

		delete(pDummy->pPrev);

		pDummy->pPrev = pDummy->pNext->pPrev;
	}

	pDummy->pNext->pNext = NULL;
	pDummy->pNext->iData = 0;
	pDummy->pPrev->pPrev = NULL;

	delete(pDummy->pNext);

	pDummy->pNext = NULL;
	pDummy->pPrev = NULL;

}

template<typename T>
int LIST<T>::CountNode()
{
	// Local Variable Declaration

	int iCounter = 1;
	NODE<T>* pTempNode = pDummy->pNext;
	// Code

	if (NULL == pDummy->pNext)
		return(0);

	while (pTempNode != pDummy->pPrev)
	{
		pTempNode = pTempNode->pNext;
		iCounter++;
	}

	return(iCounter);
}


template<typename T>
bool LIST<T>::IsEmpty()
{
	// Code

	if (pDummy->pNext)
		return(true);
	else
		return(false);
}

///////////////////////////////////		Class Iterator		////////////////////////////////


template<typename T>
void LIST<T>::Iterator::SetCurrentNode(NODE<T>* pNode)
{
	// Code

	pCurrentNode = pNode;
}

// Operator : *

template<typename T>
int LIST<T>::Iterator::operator*()
{
	// Code

	return(pCurrentNode->iData);
}

// Operator : !=

template<typename T>
bool LIST<T>::Iterator::operator!=(const Iterator& iter)
{
	// Code

	return(pCurrentNode != iter.pCurrentNode);
}

// Operator : ==

template<typename T>
bool LIST<T>::Iterator::operator==(const Iterator& iter)
{
	// Code

	return(pCurrentNode == iter.pCurrentNode);
}

// Operator : <=

template<typename T>
bool LIST<T>::Iterator::operator<=(const Iterator& iter)
{
	// Code

	return(pCurrentNode <= iter.pCurrentNode);
}

// Operator : >=

template<typename T>
bool LIST<T>::Iterator::operator>=(const Iterator& iter)
{
	// Code

	return(pCurrentNode >= iter.pCurrentNode);
}

// Operator : ++ (Pre - Increment)

template<typename T>
LIST<T>::Iterator& LIST<T>::Iterator::operator++()
{
	// Code

	if (pCurrentNode)
		pCurrentNode = pCurrentNode->pNext;

	return(*this);
}

// Operator : ++ (Post - Increment)

template<typename T>
LIST<T>::Iterator LIST<T>::Iterator::operator++(int)
{
	// Code

	Iterator TempIterator = *this;

	++(*this);

	return(TempIterator);
}

// Operator : -- (Pre - Decrement)

template<typename T>
LIST<T>::Iterator& LIST<T>::Iterator::operator--()
{
	// Code

	return(*this);
}

// Operator : -- (Post - Decrement)

template<typename T>
LIST<T>::Iterator LIST<T>::Iterator::operator--(int)
{
	// Code

	Iterator TempIterator = *this;

	--(*this);

	return(TempIterator);
}

// Operator : =

template<typename T>
LIST<T>::Iterator& LIST<T>::Iterator::operator=(NODE<T>* pNode)
{
	// Code

	pCurrentNode = pNode;

	return(*this);
}

#endif

