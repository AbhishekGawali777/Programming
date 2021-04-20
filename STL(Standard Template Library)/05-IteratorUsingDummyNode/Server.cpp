#include "list.h"

// NODE : Constructor

NODE::NODE()
{
	// Code

	pPrev = NULL;
	iData = 0;
	pNext = NULL;
}

// NODE : Destructor

NODE::~NODE()
{
	// Code

	iData = 0;

	if (pPrev)
		pPrev = NULL;

	if (pNext)
		pNext = NULL;
}

// LIST : Constructor

LIST::LIST()
{
	// Code
	
	pDummy = new NODE;

	if (NULL == pDummy)
	{
		cout << endl << endl << "Cannot Allocate Memory" << endl << endl;
		return;
	}

	pDummy->iData = 0;
	pDummy->pNext = NULL;
	pDummy->pPrev = NULL;
}

// LIST : Destructor

LIST::~LIST()
{
	// Code
	
	if (pDummy)
		DeleteAll();

	delete(pDummy);

	pDummy = NULL;
}

// LIST :: Iterator : Constructor

LIST::Iterator::Iterator()
{
	// Code

	pCurrentNode = NULL;
}

// LIST :: Iterator : Destructor

LIST::Iterator::~Iterator()
{

}

// LIST : begin()

LIST::Iterator LIST::begin()
{
	// Code

	StartIter = pDummy->pNext;

	return(StartIter);
}

// LIST : end()

LIST::Iterator LIST::end()
{
	// Code

	EndIter = pDummy;

	return(EndIter);
}

// LIST : Insert First Node

void LIST::InsertFirst(int iNum)
{
	// Local Variable Declarations

	NODE* pNewNode = NULL;

	// Code

	pNewNode = new NODE;

	if (NULL == pNewNode)
	{
		cout << endl << endl << "Cannot Allocate Memory" << endl << endl;
		return;
	}

	pNewNode->pPrev = NULL;
	pNewNode->iData = iNum;
	pNewNode->pNext = NULL;

	if (NULL == pDummy->pNext)
	{
		pNewNode->pNext = pDummy;
		pDummy->pPrev	= pNewNode;
	}
	else
	{
		pNewNode->pNext		 = pDummy->pNext;
		pDummy->pNext->pPrev = pNewNode;
	}

	pNewNode->pPrev = pDummy;
	pDummy->pNext	= pNewNode;
}

// LIST : Insert Last Node

void LIST::InsertLast(int iNum)
{
	// Local Variable Declarations
	
	NODE* pNewNode = NULL;

	// Code

	pNewNode = new NODE;

	if (NULL == pNewNode)
	{
		cout << endl << endl << "Cannot Allocate Memory" << endl << endl;
		return;
	}

	pNewNode->pPrev = NULL;
	pNewNode->iData = iNum;
	pNewNode->pNext = NULL;

	if (NULL == pDummy->pNext)
	{
		InsertFirst(iNum);
	}
	else
	{
		pDummy->pPrev->pNext = pNewNode;
		pNewNode->pNext		 = pDummy;
		pNewNode->pPrev		 = pDummy->pPrev;
		pDummy->pPrev		 = pNewNode;
	}
}

// LIST : Insert In Between Node's LIST

void LIST::InsertAtPosition(int iPosition, int iNum)
{
	// Local Variable Declarations

	NODE* pNewNode = NULL;
	NODE* pTempNode = NULL;

	// Code

	if (1 == iPosition)
	{
		InsertFirst(iNum);
	}
	else if (iPosition == (CountNode() + 1))
	{
		InsertLast(iNum);
	}
	else
	{
		pNewNode = new NODE;

		if (NULL == pNewNode)
		{
			cout << endl << endl << "Cannot Allocate Memory" << endl << endl;
			return;
		}

		pNewNode->pPrev = NULL;
		pNewNode->iData = iNum;
		pNewNode->pNext= NULL;

		pTempNode = pDummy->pNext;

		while (iPosition - 2)
		{
			pTempNode = pTempNode->pNext;
			iPosition--;
		}

		pNewNode->pNext			= pTempNode->pNext;
		pTempNode->pNext->pPrev	= pNewNode;
		pNewNode->pPrev			= pTempNode;
		pTempNode->pNext		= pNewNode;
	}
}

// LIST : Delete First Node

int LIST::DeleteFirst()
{
	// Local Variable Declaration

	int iDeletedData = 0;
	NODE* pTempNode = pDummy->pNext;

	// Code

	if (pDummy->pNext == pDummy->pPrev)
	{
		pDummy->pNext = NULL;
		pDummy->pPrev = NULL;
	}
	else
	{
		pDummy->pNext			= pTempNode->pNext;
		pTempNode->pNext->pPrev = pDummy;
	}

	iDeletedData = pTempNode->iData;

	pTempNode->pPrev = NULL;
	pTempNode->iData = 0;
	pTempNode->pNext = NULL;
	
	delete(pTempNode);

	pTempNode = NULL;
	
	return(iDeletedData);
}

// LIST : Delete Last Node

int LIST::DeleteLast()
{
	// Local Variable Declaration

	int iDeletedData = 0;
	NODE* pTempNode = NULL;

	// Code
	
	if (pDummy->pNext == pDummy->pPrev)
	{
		return(iDeletedData = DeleteFirst());
	}
	
	pTempNode               = pDummy->pPrev;
	pTempNode->pPrev->pNext = pDummy;
	pDummy->pPrev           = pTempNode->pPrev;

	iDeletedData = pTempNode->iData;

	pTempNode->pPrev = NULL;
	pTempNode->iData = 0;
	pTempNode->pNext = NULL;

	delete(pTempNode);

	pTempNode = NULL;

	return(iDeletedData);

}

// LIST : Delete In Between Node's LIST

int LIST::DeleteAtPosition(int iPosition)
{
	// Local Variable Declaration

	int iDeletedData = 0;
	NODE* pTempNode = NULL;

	// Code

	if (iPosition == 1)
	{
		iDeletedData = DeleteFirst();
	}
	else if (iPosition == CountNode())
	{
		iDeletedData = DeleteLast();
	}
	else
	{
		pTempNode = pDummy->pNext;

		while (iPosition - 1)
		{
			pTempNode = pTempNode->pNext;
			iPosition--;
		}

		iDeletedData = pTempNode->iData;

		pTempNode->pPrev->pNext = pTempNode->pNext;
		pTempNode->pNext->pPrev = pTempNode->pPrev;

		delete(pTempNode);
		pTempNode = NULL;
	}

	return(iDeletedData);
}


// LIST : Search First Occurrance

int LIST::SearchFirstOccurance(int iNumber)
{
	// Local Variable Delcarations

	int iFoundAtPos = 1;
	NODE* pTempNode = pDummy->pNext;

	// Code

	while (iNumber != pTempNode->iData && pTempNode != pDummy)
	{
		pTempNode = pTempNode->pNext;
		iFoundAtPos++;
	}

	if (pTempNode->iData != iNumber)
		return(-1);
	else
		return(iFoundAtPos);
}

// LIST : Search Last Occurrance

int LIST::SearchLastOccurance(int iNumber)
{
	// Local Variable Delcarations

	int iFoundAtPos;
	NODE* pTempNode = pDummy->pPrev;
	
	// Code

	iFoundAtPos = CountNode();

	while (pTempNode->iData != iNumber && pTempNode != pDummy)
	{
		pTempNode = pTempNode->pPrev;
		iFoundAtPos--;
	}

	if (pTempNode->iData != iNumber)
		return(-1);
	else
		return(iFoundAtPos);
}

// LIST : Search All Occurrance

int LIST::SearchAllOccurances(int iNumber)
{
	// Local Variable Delcarations

	int iFoundAtPos = 0;
	NODE* pTempNode = pDummy->pNext;

	// Code

	while (pTempNode != pDummy)
	{
		if (pTempNode->iData == iNumber)
			iFoundAtPos++;

		pTempNode= pTempNode->pNext;
	}

	if (0 == iFoundAtPos)
		return(-1);
	else
		return(iFoundAtPos);
}

// LIST : Delete All Allocated Nodes

void LIST::DeleteAll()
{
	// Code

	if (NULL == pDummy->pNext && NULL == pDummy->pPrev)
		return;

	while (pDummy->pNext != pDummy->pPrev)
	{
		pDummy->pPrev->pPrev->pNext = pDummy->pNext;
		pDummy->pNext->pPrev		= pDummy->pPrev->pPrev;

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

// LIST : Is List Empty

bool LIST::IsEmpty()
{
	// Code
	if (pDummy->pNext)
		return(0);
	else
		return(1);
}

// LIST : Count Number Of nodes present

int LIST::CountNode()
{
	// Local Variable Declaration

	int iCounter = 1;
	NODE* pTempNode = pDummy->pNext;
	// Code

	if (NULL == pDummy->pNext)
		return(0);

	while (pTempNode != pDummy)
	{
		pTempNode = pTempNode->pNext;
		iCounter++;
	}

	return(iCounter);
}

///////////////////////////////////		Class Iterator		////////////////////////////////


void LIST::Iterator::SetCurrentNode(NODE* pNode)
{
	pCurrentNode = pNode;
}

// Operator : *

int LIST::Iterator::operator*()
{
	// Code

	return(pCurrentNode->iData);
}

// Operator : !=

bool LIST::Iterator::operator!=(const Iterator& iter)
{
	// Code

	return(pCurrentNode != iter.pCurrentNode);
}

// Operator : ==

bool LIST::Iterator::operator==(const Iterator& iter)
{
	// Code

	return(pCurrentNode == iter.pCurrentNode);
}

// Operator : <=

bool LIST::Iterator::operator<=(const Iterator& iter)
{
	// Code

	return(pCurrentNode <= iter.pCurrentNode);
}

// Operator : >=

bool LIST::Iterator::operator>=(const Iterator& iter)
{
	// Code
	
	return(pCurrentNode >= iter.pCurrentNode);
}

// Operator : ++ (Pre - Increment)

LIST::Iterator& LIST::Iterator::operator++()
{
	// Code

	if(pCurrentNode)
		pCurrentNode = pCurrentNode->pNext;

	return(*this);
}

// Operator : ++ (Post - Increment)

LIST::Iterator LIST::Iterator::operator++(int)
{
	// Code

	Iterator TempIterator = *this;

	++(*this);

	return(TempIterator);
}

// Operator : -- (Pre - Decrement)

LIST::Iterator& LIST::Iterator::operator--()
{

	// Code

	return(*this);
}

// Operator : -- (Post - Decrement)

LIST::Iterator LIST::Iterator::operator--(int)
{
	// Code

	Iterator TempIterator = *this;
	
	--(*this);
	
	return(TempIterator);
}

// Operator : =

LIST::Iterator& LIST::Iterator::operator=(NODE* pNode)
{
	// Code

	pCurrentNode = pNode;

	return(*this);

}
