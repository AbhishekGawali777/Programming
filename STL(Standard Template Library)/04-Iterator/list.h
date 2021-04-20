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

	class Iterator
	{
		NODE* pCurrentNode;

	public:

		Iterator();
		~Iterator();
		
		// Function Declarations

		NODE* SetCurrentNode();
		NODE* GetCurrentNode();
	};

	LIST::Iterator begin();
	LIST::Iterator end();

};

// Nacked Function Declarations

void DisplayIterator(LIST*);

#endif
