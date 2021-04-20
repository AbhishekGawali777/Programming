/////////////////////////////////////		 Header File (list.h)		///////////////////////////////////////

#pragma once

// Header Files

#include <iostream>
#include <iomanip>

// Class Declarations

using namespace std;

template<typename T>
int MyMain(T);

template<typename T>
class NODE
{
	NODE<T>* pPrev;
	T        t_Data;
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
	NODE<T>* pLast;
	NODE<T>* pFirst;

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
	int	 IsEmpty();
	void DeleteAll();
	int	 CountNode();

};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////		Client File (Client.cpp)	///////////////////////////////////////


#include "List.h"

int main(void)
{
	// Local Variable Declarations
	int iChoice;

	// Code

	do
	{
		cout << endl << endl << "Which Type Of List You Want To Create .?" << endl << endl;

		cout << "1.) Integer (int)" << endl;
		cout << "2.) Character (char)" << endl;
		cout << "3.) Single precision Floating Point (Float)." << endl;
		cout << "4.) Double Precision Floating Point (Double)." << endl;
		cout << "5.) Exit." << endl << endl;

		cin >> iChoice;

		switch (iChoice)
		{
		case 1:
			MyMain(10);
			break;

		case 2:
			MyMain('A');
			break;

		case 3:
			MyMain(10.20f);
			break;

		case 4:
			MyMain(3.1415963789);
			break;

		case 5:
			return(0);
		}

	} while (1);

}

template <typename T>
int MyMain(T t_Type)
{
	LIST<T> ObjList;
	T t_Data;
	int iPosition, iChoice;

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
					cout << "Enter Data : ";
					cin >> t_Data;

					cout << endl;

					ObjList.InsertFirst(t_Data);

					break;

				case 2:
					cout << "Enter Data : ";
					cin >> t_Data;

					cout << endl;

					ObjList.InsertLast(t_Data);

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

					cout << "Enter Data : ";
					cin >> t_Data;
					cout << endl;

					ObjList.InsertAtPosition(iPosition, t_Data);

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
					t_Data = ObjList.DeleteFirst();

					break;

				case 2:
					t_Data = ObjList.DeleteLast();

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

					t_Data = ObjList.DeleteAtPosition(iPosition);

					break;

				case 4:
					break;

				default:

					cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl;
					break;
				}

				cout << endl << "Deleted Data Is : " << t_Data << endl << endl;

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

				cout << "Enter Data To Find Occurance Of : ";
				cin >> t_Data;

				switch (iChoice)
				{
				case 1:

					iPosition = ObjList.SearchFirstOccurance(t_Data);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << t_Data << endl;
					else
						cout << endl << "First Occurance Of Data '" << t_Data << "' Found At Position '" << iPosition << "' In The List" << endl << endl;

					break;

				case 2:

					iPosition = ObjList.SearchLastOccurance(t_Data);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << t_Data << endl;
					else
						cout << endl << "Last Occurance Of Data '" << t_Data << "' Found At Position '" << iPosition << "' In The List" << endl << endl;

					break;

				case 3:
					iPosition = ObjList.SearchAllOccurances(t_Data);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << t_Data << endl << endl;
					else
						cout << endl << "There are '" << iPosition << "' Occurances Found For Data '" << t_Data << "' In The List" << endl << endl;

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

			iPosition = ObjList.CountNode();

			cout << endl << "Number Of Nodes In The List Are : " << iPosition << endl << endl;
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
	pFirst = NULL;
	pLast = NULL;
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

	pNewNode = new NODE<T>;

	if (NULL == pNewNode)
	{
		cout << endl << "Memory Allocation failed" << endl << endl;
		return;
	}

	pNewNode->t_Data = tData;

	if (NULL == pFirst && NULL == pLast)
	{
		InsertFirst(tData);

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
		InsertFirst(tData);
		return;
	}
	else if (iPosition == this->CountNode() + 1)
	{
		InsertLast(tData);
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
		iDeletedData = DeleteLast();
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
	NODE<T>* pHead = pFirst;
	NODE<T>* pTail = pLast;

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
	NODE<T>* pHead = pFirst;
	NODE<T>* pTail = pLast;

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
	NODE<T>* pHead = pFirst;
	NODE<T>* pTail = pLast;

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
