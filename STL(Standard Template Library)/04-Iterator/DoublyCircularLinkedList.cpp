/////////////////////////////////////		 Header File (list.h)		///////////////////////////////////////


#ifndef LIST_H

#define LIST_H

// Header Files

#include <iostream>
#include <iomanip>

// Class Declarations

using namespace std;

class NODE
{
	NODE* pPrev;
	int		iData;
	NODE* pNext;

public:

	// Functions Declarations

	NODE();
	~NODE();

	friend class LIST;
};


class LIST
{
	NODE* pLast;
	NODE* pFirst;

public:

	// Function Declarations

	LIST();
	~LIST();

	void InsertFirst(int);
	void InsertLast(int);
	void InsertAtPosition(int, int);

	int DeleteFirst();
	int DeleteLast();
	int DeleteAtPosition(int);

	int SearchFirstOccurance(int);
	int SearchLastOccurance(int);
	int SearchAllOccurances(int);

	void Display();
	int	 IsEmpty();
	void DeleteAll();
	int	 CountNode();

};

#endif



///////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////		Client File (Client.cpp)	///////////////////////////////////////


#include "List.h"

int main(void)
{
	// Loacal Variable Declarations

	LIST ObjList;
	int iNumber, iPosition, iChoice;

	// Code
	do
	{

		cout << "1.) Insert." << endl;
		cout << "2.) Delete." << endl;
		cout << "3.) Search." << endl;
		cout << "4.) Node Count." << endl;
		cout << "5.) Exit." << endl << endl;


		cout << "Enter Your Choice : ";
		cin >> iChoice;
		cout << endl;


		switch (iChoice)
		{
		case 1:

			do
			{

				cout << setw(15) << "1.) Insert At First Position." << endl;
				cout << "2.) Insert At Last Position." << endl;
				cout << "3.) Insert In Between The List." << endl;
				cout << "4.) Back To Main Menu." << endl << endl;

				cout << "Enter Choice For Method Of Insertion : ";
				cin >> iChoice;

				cout << endl << endl;

				switch (iChoice)
				{
				case 1:
					cout << "Enter Number : ";
					cin >> iNumber;

					cout << endl;

					ObjList.InsertFirst(iNumber);

					break;

				case 2:
					cout << "Enter Number : ";
					cin >> iNumber;

					cout << endl;

					ObjList.InsertLast(iNumber);

					break;

				case 3:

					cout << "Enter Position : ";
					cin >> iPosition;

					cout << endl;

					if (iPosition > (ObjList.CountNode() + 1) || iPosition < 1)
					{
						cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Position +-+-+-+-+-+-+-+-+-+-" << endl;
						break;
					}

					printf("\n");

					cout << "Enter Number : ";
					cin >> iNumber;
					cout << endl;

					ObjList.InsertAtPosition(iPosition, iNumber);

					break;

				case 4:
					break;

				default:

					cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl;
					break;
				}

				ObjList.Display();

			} while (4 != iChoice);

			break;

		case 2:

			do
			{
				cout << endl;
				cout << endl;

				if (ObjList.IsEmpty())
				{
					cout << endl << "There Is Nothing To Delete, As List Is Empty" << endl << endl;
					break;
				}

				cout << "1.) Delete From First Position" << endl;
				cout << "2.) Delete From Last Position" << endl;
				cout << "3.) Delete In Between The List" << endl;
				cout << "4.) Back To Main Menu" << endl << endl;

				cout << "Enter Choice For Method Of Deletion : ";
				cin >> iChoice;


				switch (iChoice)
				{

				case 1:
					iNumber = ObjList.DeleteFirst();

					break;

				case 2:
					iNumber = ObjList.DeleteLast();

					break;

				case 3:

					cout << "Enter Position : ";
					cin >> iPosition;

					cout << endl;

					if (iPosition > (ObjList.CountNode()) || iPosition < 1)
					{
						cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Position +-+-+-+-+-+-+-+-+-+-" << endl;
						break;
					}

					iNumber = ObjList.DeleteAtPosition(iPosition);

					break;

				case 4:
					break;

				default:

					cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl;
					break;
				}

				cout << endl << "Deleted Node Is : " << iNumber << endl << endl;

				ObjList.Display();

			} while (4 != iChoice);

			break;

		case 3:

			do
			{
				cout << endl << endl;

				if (ObjList.IsEmpty())
				{
					cout << endl << "There Is Nothing To Search, As List Is Empty" << endl << endl;
					break;
				}

				cout << "1.) Search First Occurance Data" << endl;
				cout << "2.) Search Last Occurance Data" << endl;
				cout << "3.) Search All Occurances Data" << endl;
				cout << "4.) Back To Main Menu" << endl << endl;

				cout << "Enter Choice For Method Of Searching : ";
				cin >> iChoice;
				cout << endl;

				if (4 == iChoice)
					break;
				else if (iChoice > 4 || iChoice < 1)
				{
					cout << endl << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl << endl;
					break;
				}

				cout << "Enter Number To Find Occurance Of : ";
				cin >> iNumber;

				switch (iChoice)
				{
				case 1:

					iPosition = ObjList.SearchFirstOccurance(iNumber);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << iNumber << endl;
					else
						cout << endl << "First Occurance Of Data '" << iNumber << "' Found At Position '" << iPosition << "' In The List" << endl << endl;

					break;

				case 2:

					iPosition = ObjList.SearchLastOccurance(iNumber);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << iNumber << endl;
					else
						cout << endl << "Last Occurance Of Data '" << iNumber << "' Found At Position '" << iPosition << "' In The List" << endl << endl;

					break;

				case 3:
					iPosition = ObjList.SearchAllOccurances(iNumber);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << iNumber << endl << endl;
					else
						cout << endl << "There are '" << iPosition << "' Occurances Found For Number '" << iNumber << "' In The List" << endl << endl;

					break;


				case 4:
					break;

				default:

					cout << endl << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl << endl;
					break;
				}

				ObjList.Display();

			} while (4 != iChoice);

			break;

		case 4:


			if (ObjList.IsEmpty())
			{
				cout << endl << endl << "Not A Single Node Present In The List, As List Is Empty" << endl << endl;
			}

			iNumber = ObjList.CountNode();

			cout << endl << "Number Of Nodes In The List Are : " << iNumber << endl << endl;
			break;

		case 5:
			ObjList.Display();
			ObjList.DeleteAll();

			return(0);

		default:
			cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl << endl;

		}

	} while (1);


	return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////		Server File (Server.cpp)	///////////////////////////////////////



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

	iDeletedData = pLast->iData;

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
