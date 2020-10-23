#include <stdio.h>

int main(void)
{
	// Variable Declarations

	int ABG_iNum;
	int* ABG_ptr = NULL;
	int** ABG_pptr = NULL;

	ABG_iNum = 10;

	printf("\n\n");

	printf("+-+-+-+-+-+-+-+-+-+- BEFORE ptr = &ABG_iNum +-+-+-+-+-+-+-+-+-+\n\n");

	printf("Value Of 'ABG_iNum'		= %d\n", ABG_iNum);
	printf("Address Of 'ABG_iNum'		= %p\n", &ABG_iNum);
	printf("Value At Address Of 'ABG_iNum'	= %d\n", *(&ABG_iNum));

	ABG_ptr = &ABG_iNum;

	printf("\n\n");

	printf("+-+-+-+-+-+-+-+-+-+- AFTER ptr = &ABG_iNum +-+-+-+-+-+-+-+-+-+\n\n");

	printf("Value Of 'ABG_iNum'			= %d\n", ABG_iNum);
	printf("Address Of 'ABG_iNum'			= %p\n", ABG_ptr);
	printf("Value At Address Of 'ABG_iNum'		= %d\n", *ABG_ptr);

	ABG_pptr = &ABG_ptr;

	printf("\n\n");

	printf("+-+-+-+-+-+-+-+-+-+- AFTER ptr = &ABG_ptr +-+-+-+-+-+-+-+-+-+\n\n");

	printf("Value Of 'ABG_iNum'					= %d\n", ABG_iNum);
	printf("Address Of 'ABG_iNum' (ptr)				= %p\n", ABG_ptr);
	printf("Address Of 'ABG_ptr' (pptr)				= %p\n", ABG_pptr);
	printf("Value At Address Of 'ABG_iNum' (*pptr)			= %p\n", *ABG_pptr);
	printf("Value At Address Of 'ABG_iNum' (*ptr)(*pptr)		= %d\n", **ABG_pptr);

	printf("\n\n");

	return(0);
}