#include "List.h"

// Nacked Function Declarations

void DisplayIterator(LIST&);

// main()

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
	T tData;
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
					cout << "Enter Number : ";
					cin >> tData;

					cout << endl;

					ObjList.InsertFirst(tData);

					break;

				case 2:
					cout << "Enter Number : ";
					cin >> tData;

					cout << endl;

					ObjList.InsertLast(tData);

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
					cin >> tData;
					cout << endl;

					ObjList.InsertAtPosition(iPosition, tData);

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
					tData = ObjList.DeleteFirst();

					break;

				case 2:
					tData = ObjList.DeleteLast();

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

					tData = ObjList.DeleteAtPosition(iPosition);

					break;

				case 4:
					break;

				default:

					cout << "+-+-+-+-+-+-+-+-+-+- Enter valid Choice +-+-+-+-+-+-+-+-+-+-" << endl;
					break;
				}

				cout << endl << "Deleted Node Is : " << tData << endl << endl;

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
				cin >> tData;

				switch (iChoice)
				{
				case 1:

					iPosition = ObjList.SearchFirstOccurance(tData);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << tData << endl;
					else
						cout << endl << "First Occurance Of Data '" << tData << "' Found At Position '" << iPosition << "' In The List" << endl << endl;

					break;

				case 2:

					iPosition = ObjList.SearchLastOccurance(tData);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << tData << endl;
					else
						cout << endl << "Last Occurance Of Data '" << tData << "' Found At Position '" << iPosition << "' In The List" << endl << endl;

					break;

				case 3:
					iPosition = ObjList.SearchAllOccurances(tData);

					if (-1 == iPosition)
						cout << endl << "No Occurance Found For Entered Data = " << tData << endl << endl;
					else
						cout << endl << "There are '" << iPosition << "' Occurances Found For Number '" << tData << "' In The List" << endl << endl;

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

			tData = ObjList.CountNode();

			cout << endl << "Number Of Nodes In The List Are : " << tData << endl << endl;
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
