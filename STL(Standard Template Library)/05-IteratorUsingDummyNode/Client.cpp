#include "list.h"

// Nacked Function Declarations

void DisplayIterator(LIST&);

// main()

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

				DisplayIterator(ObjList);

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
						continue;
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

				DisplayIterator(ObjList);

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

				DisplayIterator(ObjList);

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
			DisplayIterator(ObjList);
			ObjList.DeleteAll();

			return(0);

		default:
			cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl << endl;

		}

	} while (1);

	cin.get();
	return(0);
}

// DisplayIterator()

void DisplayIterator(LIST& list)
{
	// Code

	if (list.IsEmpty())
	{
		cout << endl << endl << "Linked List Is Empty ";		
	}
	else
	{
		cout << endl << endl << "Linked List Is : ";
	
		for (LIST::Iterator iter = list.begin(); iter != list.end(); ++iter)
			cout << "<-|" << *iter << "|->";
	}

	cout << endl << endl;
}
