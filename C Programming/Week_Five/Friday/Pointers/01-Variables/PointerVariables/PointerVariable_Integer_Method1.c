#include <stdio.h>

int main(void)
{
	int ABG_iNum;
	int* ABG_ptr = NULL;

	ABG_iNum = 124;

	printf("\n\n");
	printf("******** Before ABG_ptr = &ABG_iNum *********\n\n");
	printf("Value Of 'ABG_iNum'		=		%d\n\n", ABG_iNum);
	printf("Address Of 'ABG_iNum'		=		%p\n\n", &ABG_iNum);
	printf("Value At Address Of 'ABG_iNum'	=		%d\n\n", *(&ABG_iNum));

	ABG_ptr = &ABG_iNum;

	printf("\n\n");
	printf("******** After ABG_ptr = &ABG_iNum *********\n\n");
	printf("Value Of 'ABG_iNum'		=		%d\n\n", ABG_iNum);
	printf("Address Of 'ABG_iNum'		=		%p\n\n", &ABG_ptr);
	printf("Value At Address Of 'ABG_iNum'	=		%d\n\n", *ABG_ptr);

	return(0);
}