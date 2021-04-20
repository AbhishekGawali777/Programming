#include "List.h"

NODE::NODE()
{
	pPrev = NULL;
	iData = 0;
	pNext = NULL;
}

NODE :: ~NODE()
{
	this->iData = 0;

	if (pPrev)
		pPrev = NULL;

	if (pNext)
		pNext = NULL;
}

LIST::LIST()
{
	this->pFirst = NULL;
	this->pLast = NULL;
}

LIST :: ~LIST()
{
	if (NULL != pFirst || NULL != pLast)
	{
		this->DeleteAll();
	}

}

void LIST::InsertFirst(int iNumber)
{
	// Local Variable

	NODE* pNewNode = NULL;

	// Code

	pNewNode = new NODE;

	if (NULL == pNewNode)
	{
		cout << endl << "Memory Allocation failed" << endl << endl;
		return;
	}

	pNewNode->iData = iNumber;

	if (pFirst == NULL && pLast == NULL)
	{
		pFirst = pNewNode;
		pLast = pNewNode;
		pFirst->pNext = pFirst;
		pFirst->pPrev = pLast;

		return;
	}

	pNewNode->pNext = pFirst;
	pNewNode->pPrev = pLast;
	pFirst->pPrev = pNewNode;
	pFirst = pNewNode;
	pLast->pNext = pNewNode;
}

void LIST::InsertLast(int iNumber)
{
	// Local Variable

	NODE* pNewNode = NULL;

	// Code

	pNewNode = new NODE;

	if (NULL == pNewNode)
	{
		cout << endl << "Memory Allocation failed" << endl << endl;
		return;
	}

	pNewNode->iData = iNumber;

	if (NULL == pFirst && NULL == pLast)
	{
		this->InsertFirst(iNumber);

		return;
	}

	pNewNode->pNext = pLast->pNext;
	pNewNode->pPrev = pLast;
	pLast->pNext = pNewNode;
	pFirst->pPrev = pNewNode;
	pLast = pNewNode;
}

void LIST::InsertAtPosition(int iPosition, int iNumber)
{
	// Local variable Declarations

	NODE* pTempNode = NULL;
	NODE* pNewNode = NULL;

	// Code

	if (iPosition > this->CountNode() + 1 || iPosition < 1)
	{
		cout << endl << endl << "+-+-+-+-+-+-+-+-+-+- Enter Valid Position +-+-+-+-+-+-+-+-+-+-" << endl << endl;
		return;
	}
	else if (this->IsEmpty() || 1 == iPosition)
	{
		//cout << endl << endl << "Calling InsertFirst()" << endl << endl;
		this->InsertFirst(iNumber);
		return;
	}
	else if (iPosition == this->CountNode() + 1)
	{
		this->InsertLast(iNumber);
		return;
	}

	pNewNode = new NODE;

	if (NULL == pNewNode)
	{
		cout << endl << endl << "Memory Allocation Failed" << endl << endl;
		return;
	}

	pNewNode->iData = iNumber;

	pTempNode = pFirst;

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

int LIST::DeleteFirst()
{
	// Local Variable Declaration

	int iDeletedData = 0;

	// Code

	if (pFirst != pLast)
	{
		pLast->pNext = pFirst->pNext;
		pFirst->pNext->pPrev = pLast;
	}

	iDeletedData = pFirst->iData;

	delete(pFirst);

	if (pFirst != pLast)
		pFirst = pLast->pNext;
	else
	{
		pFirst = NULL;
		pLast = NULL;
	}

	return(iDeletedData);
}

int LIST::DeleteLast()
{
	// Local Variable Declaration

	int iDeletedData = 0;
	
	// Code

	if (pFirst != pLast)
	{
		pFirst->pPrev = pLast->pPrev;
		pLast->pPrev->pNext = pFirst;
	}

	iDeletedData = pLast->iData ;

	if (pFirst != pLast)
		pLast = pFirst->pPrev;
	else
	{
		pFirst = NULL;
		pLast = NULL;
	}

	return(iDeletedData);
}

int LIST::DeleteAtPosition(int iPosition)
{
	// local Variable Declarations

	int	  iDeletedData = 0;
	NODE* pTempNode = NULL;

	// Code

	if (1 == iPosition)
	{
		iDeletedData = this->DeleteFirst();
		return (iDeletedData);
	}
	else if (iPosition == this->CountNode())
	{
		iDeletedData = this->DeleteLast();
		return(iDeletedData);
	}

	pTempNode = this->pFirst;

	while (iPosition - 1)
	{
		pTempNode = pTempNode->pNext;
		iPosition--;
	}

	iDeletedData = pTempNode->iData;

	pTempNode->pPrev->pNext = pTempNode->pNext;
	pTempNode->pNext->pPrev = pTempNode->pPrev;

	delete(pTempNode);

	return(iDeletedData);
}

int LIST::SearchFirstOccurance(int iNumber)
{
	// Local Variable Delcarations

	int iOccurance = 1;
	NODE* pHead = this->pFirst;
	NODE* pTail = this->pLast;

	// Code

	while (iNumber != pHead->iData && pHead != pTail)
	{
		pHead = pHead->pNext;
		iOccurance++;
	}

	if (pHead->iData != iNumber)
		return(-1);
	else
		return(iOccurance);
}

int LIST::SearchLastOccurance(int iNumber)
{
	// Local Variable Delcarations

	int iOccurance;
	NODE* pHead = this->pFirst;
	NODE* pTail = this->pLast;

	// Code

	iOccurance = this->CountNode();

	while (pTail->iData != iNumber && pHead != pTail)
	{
		pTail = pTail->pPrev;
		iOccurance--;
	}

	if (pTail->iData != iNumber)
		return(-1);
	else
		return(iOccurance);
}

int LIST::SearchAllOccurances(int iNumber)
{

	// Local Variable Delcarations

	int iOccurance = 0;
	NODE* pHead = this->pFirst;
	NODE* pTail = this->pLast;

	// Code

	while (pHead != pTail)
	{
		if (pHead->iData == iNumber)
			iOccurance++;

		pHead = pHead->pNext;
	}

	if (pHead->iData == iNumber)
		iOccurance++;

	if (0 == iOccurance)
		return(-1);
	else
		return(iOccurance);
}

void LIST::DeleteAll()
{
	// Code

	if (NULL == pFirst && NULL == pLast)
		return;

	while (pFirst != pLast)
	{
		pLast->pPrev->pNext = pLast->pNext;
		pFirst->pPrev = pLast->pPrev;

		delete(pLast);

		pLast = pFirst->pPrev;
	}

	pFirst->pPrev = NULL;
	pFirst->pNext = NULL;

	delete(pFirst);

	pFirst = NULL;
	pLast = NULL;

}

int LIST::CountNode()
{
	// Local Variable Declarartions

	int iCount = 1;
	NODE* pHead = pFirst;
	NODE* pTail = pLast;

	// Code

	if (NULL == pFirst && NULL == pLast)
		return(0);

	while (pHead != pLast)
	{
		pHead = pHead->pNext;

		iCount++;
	}

	return(iCount);
}

void LIST::Display()
{
	// Local Variable

	NODE* ppHead = pFirst;
	NODE* ppTail = pLast;
	// Code

	if (this->IsEmpty())
	{
		cout << endl << endl << "******************** Linked List Is Empty *******************" << endl << endl;
		return;
	}

	cout << endl << endl << "		Linked List Is : ";

	while (ppHead != ppTail)
	{
		cout << "->|" << ppHead->iData << "|";

		ppHead = ppHead->pNext;
	}

	cout << "->|" << ppHead->iData << "|" << endl << endl << endl;
}

int LIST::IsEmpty()
{
	// Code

	if (NULL == pFirst && NULL == pLast)
		return(1);
	else
		return(0);
}
