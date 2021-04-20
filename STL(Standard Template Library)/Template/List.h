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
	T t_Data;
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

#endif
