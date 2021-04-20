#include "List.h"

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
	this->t_Data = 0;

	if (pPrev)
		pPrev = NULL;

	if (pNext)
		pNext = NULL;
}

template<typename T>
LIST<T>::LIST()
{
	this->pFirst = NULL;
	this->pLast = NULL;
}

template<typename T>
LIST<T> :: ~LIST()
{
	if (NULL != pFirst)
	{
		DeleteAll();
	}

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

	pNewNode->t_Data = tData;

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

template <typename T>
void LIST<T>::InsertLast(T tData)
{
	// Local Variable

	NODE<T>* pNewNode = NULL;

	// Code

	pNewNode = new NODE;

	if (NULL == pNewNode)
	{
		cout << endl << "Memory Allocation failed" << endl << endl;
		return;
	}

	pNewNode->t_Data = tData;

	if (NULL == pFirst && NULL == pLast)
	{
		this->InsertFirst(tData);

		return;
	}

	pNewNode->pNext = pLast->pNext;
	pNewNode->pPrev = pLast;
	pLast->pNext = pNewNode;
	pFirst->pPrev = pNewNode;
	pLast = pNewNode;
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

	pNewNode->t_Data = tData;

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

template <typename T>
T LIST<T>::DeleteFirst()
{
	// Local Variable Declaration

	int iDeletedData = 0;

	// Code

	if (pFirst != pLast)
	{
		pLast->pNext = pFirst->pNext;
		pFirst->pNext->pPrev = pLast;
	}

	iDeletedData = pFirst->t_Data;

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

template <typename T>
T LIST<T>::DeleteLast()
{
	// Local Variable Declaration

	int iDeletedData = 0;

	// Code

	if (pFirst != pLast)
	{
		pFirst->pPrev = pLast->pPrev;
		pLast->pPrev->pNext = pFirst;
	}

	iDeletedData = pLast->t_Data;

	if (pFirst != pLast)
		pLast = pFirst->pPrev;
	else
	{
		pFirst = NULL;
		pLast = NULL;
	}

	return(iDeletedData);
}

template <typename T>
T LIST<T>::DeleteAtPosition(int iPosition)
{
	// local Variable Declarations

	int	  iDeletedData = 0;
	NODE<T>* pTempNode = NULL;

	// Code

	if (1 == iPosition)
	{
		iDeletedData = DeleteFirst();
		return (iDeletedData);
	}
	else if (iPosition == CountNode())
	{
		iDeletedData = this->DeleteLast();
		return(iDeletedData);
	}

	pTempNode = pFirst;

	while (iPosition - 1)
	{
		pTempNode = pTempNode->pNext;
		iPosition--;
	}

	iDeletedData = pTempNode->t_Data;

	pTempNode->pPrev->pNext = pTempNode->pNext;
	pTempNode->pNext->pPrev = pTempNode->pPrev;

	delete(pTempNode);

	return(iDeletedData);
}

template <typename T>
int LIST<T>::SearchFirstOccurance(T tData)
{
	// Local Variable Delcarations

	int iOccurance = 1;
	NODE<T>* pHead = pFirst;
	NODE<T>* pTail = pLast;

	// Code

	while (tData != pHead->t_Data && pHead != pTail)
	{
		pHead = pHead->pNext;
		iOccurance++;
	}

	if (pHead->t_Data != tData)
		return(-1);
	else
		return(iOccurance);
}

template <typename T>
int LIST<T>::SearchLastOccurance(T tData)
{
	// Local Variable Delcarations

	int iOccurance;
	NODE<T>* pHead = this->pFirst;
	NODE<T>* pTail = this->pLast;

	// Code

	iOccurance = this->CountNode();

	while (pTail->t_Data != tData && pHead != pTail)
	{
		pTail = pTail->pPrev;
		iOccurance--;
	}

	if (pTail->t_Data != tData)
		return(-1);
	else
		return(iOccurance);
}

template <typename T>
int LIST<T>::SearchAllOccurances(T tData)
{

	// Local Variable Delcarations

	int iOccurance = 0;
	NODE<T>* pHead = this->pFirst;
	NODE<T>* pTail = this->pLast;

	// Code

	while (pHead != pTail)
	{
		if (pHead->t_Data == tData)
			iOccurance++;

		pHead = pHead->pNext;
	}

	if (pHead->t_Data == tData)
		iOccurance++;

	if (0 == iOccurance)
		return(-1);
	else
		return(iOccurance);
}

template<typename T>
void LIST<T>::DeleteAll()
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

template<typename T>
int LIST<T>::CountNode()
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

template<typename T>
void LIST<T>::Display()
{
	// Local Variable

	NODE<T>* ppHead = pFirst;
	NODE<T>* ppTail = pLast;
	// Code

	if (this->IsEmpty())
	{
		cout << endl << endl << "******************** Linked List Is Empty *******************" << endl << endl;
		return;
	}

	cout << endl << endl << "		Linked List Is : ";

	while (ppHead != ppTail)
	{
		cout << "->|" << ppHead->t_Data << "|";

		ppHead = ppHead->pNext;
	}

	cout << "->|" << ppHead->t_Data << "|" << endl << endl << endl;
}

template<typename T>
int LIST<T>::IsEmpty()
{
	// Code

	if (NULL == pFirst && NULL == pLast)
		return(1);
	else
		return(0);
}
