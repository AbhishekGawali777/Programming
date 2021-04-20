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
	int	  iData;
	NODE* pNext;

public:

	// Functions Declarations

	NODE();
	~NODE();

	friend class LIST;
};


class LIST
{
	NODE* pDummy;

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

	bool IsEmpty();
	void DeleteAll();
	int	 CountNode();

	class Iterator
	{
		NODE* pCurrentNode;

	public:

		Iterator();
		~Iterator();

		// Function Declarations

		NODE* GetCurrentNode();
		void  SetCurrentNode(NODE*);

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
		Iterator& operator =(NODE*);

	};

	LIST::Iterator begin();
	LIST::Iterator end();

private:
	Iterator StartIter;
	Iterator EndIter;
};

#endif
