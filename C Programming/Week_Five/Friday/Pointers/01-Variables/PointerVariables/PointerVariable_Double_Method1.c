#include <stdio.h>

int main(void)
{
	double ABG_dNum;
	double* ABG_ptr = NULL;

	ABG_dNum = 239756.4498722;

	printf("\n\n");
	printf("******** Before ABG_ptr = &ABG_dNum *********\n\n");
	printf("Value Of 'ABG_dNum'		=		%f\n\n", ABG_dNum);
	printf("Address Of 'ABG_dNum'		=		%p\n\n", &ABG_dNum);
	printf("Value At Address Of 'ABG_dNum'	=		%f\n\n", *(&ABG_dNum));

	ABG_ptr = &ABG_dNum;

	printf("\n\n");
	printf("******** After ABG_ptr = &ABG_dNum *********\n\n");
	printf("Value Of 'ABG_dNum'		=		%f\n\n", ABG_dNum);
	printf("Address Of 'ABG_dNum'		=		%p\n\n", &ABG_ptr);
	printf("Value At Address Of 'ABG_dNum'	=		%f\n\n", *ABG_ptr);

	return(0);
}