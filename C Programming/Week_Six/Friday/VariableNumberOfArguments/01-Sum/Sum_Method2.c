#include <stdio.h>
#include <stdarg.h>

int main(void)
{
	// Function Declaration

	int ABG_CalculateSum(int, ...);

	// Variable Declaration

	int ABG_iAnswer;

	// Code 

	printf("\n\n");

	ABG_iAnswer = ABG_CalculateSum(4, 20, 30, 40, 50);
	printf("Answer :\t%d", ABG_iAnswer);

	printf("\n\n");

	ABG_iAnswer = ABG_CalculateSum(8, 1, 1, 1, 1, 1, 1, 1, 1);
	printf("Answer :\t%d", ABG_iAnswer);

	printf("\n\n");

	ABG_iAnswer = ABG_CalculateSum(0);
	printf("Answer :\t%d", ABG_iAnswer);

	return(0);
}

int ABG_CalculateSum(int ABG_iCount, ...)
{
	// Function Declaration

	int ABG_vaCalculateSum(int, va_list);

	// Variable Declaration

	int ABG_iNumber;
	int ABG_SumOfIntegers = 0;

	va_list ABG_list;

	// Code

	va_start(ABG_list, ABG_iCount);

	ABG_SumOfIntegers = ABG_vaCalculateSum(ABG_iCount, ABG_list);

	va_end(ABG_list);

	return(ABG_SumOfIntegers);
}

int ABG_vaCalculateSum(int ABG_iCount, va_list ABG_list)
{
	// Variable Declaration

	int ABG_iNumber;
	int ABG_SumOfIntergers = 0;

	while (ABG_iCount)
	{
		ABG_iNumber = va_arg(ABG_list, int);
		ABG_SumOfIntergers = ABG_SumOfIntergers + ABG_iNumber;
		ABG_iCount--;
	}

	return(ABG_SumOfIntergers);
}