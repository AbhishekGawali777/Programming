#include <stdio.h>
#include <stdarg.h>

#define ABG_NUM_TO_FIND				6
#define ABG_NUMBER_OF_ELEMENTS		12

int main(void)
{
	// Function Declaration

	void ABG_FindNumber(int, int, ...);

	// Code

	printf("\n\n");

	ABG_FindNumber(ABG_NUM_TO_FIND, ABG_NUMBER_OF_ELEMENTS, 1, 6, 9, 3, 14, 7, 1, 6, 47, 6, 5, 4);

	return(0);
}

void ABG_FindNumber(int ABG_NumberToFind, int ABG_iNumOfElements, ...)
{
	// Function Declaration

	int ABG_vaFindNumber(int, int, va_list);

	// Variable Declarations

	int ABG_iNumber;
	int ABG_iCount = 0;

	va_list ABG_NumberList;

	// Code

	va_start(ABG_NumberList, ABG_iNumOfElements);

	ABG_iCount = ABG_vaFindNumber(ABG_NumberToFind, ABG_iNumOfElements, ABG_NumberList);
	
	if (ABG_iCount == 0)
		printf("Number %d Could Not Be Found..!!\n\n", ABG_NumberToFind);
	else
		printf("Number %d Is Found %d Times..!!\n\n", ABG_NumberToFind, ABG_iCount);

	va_end(ABG_NumberList);
}

int ABG_vaFindNumber(int ABG_NumberToFind, int ABG_iNumberOfElements, va_list ABG_NumberList)
{
	// Variable Declarations
	int ABG_iNumber;
	int ABG_iCount = 0;

	// Code

	while (ABG_iNumberOfElements)
	{
		ABG_iNumber = va_arg(ABG_NumberList, int);

		if (ABG_iNumber == ABG_NumberToFind)
			ABG_iCount++;

		ABG_iNumberOfElements--;
	}

	return(ABG_iCount);
}