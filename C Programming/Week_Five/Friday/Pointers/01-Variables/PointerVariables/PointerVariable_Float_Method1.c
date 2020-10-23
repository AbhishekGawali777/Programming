#include <stdio.h>

int main(void)
{
	float ABG_fNum;
	float* ABG_ptr = NULL;

	ABG_fNum = 47.172f;

	printf("\n\n");
	printf("******** Before ABG_ptr = &ABG_fNum *********\n\n");
	printf("Value Of 'ABG_fNum'		=		%f\n\n", ABG_fNum);
	printf("Address Of 'ABG_fNum'		=		%p\n\n", &ABG_fNum);
	printf("Value At Address Of 'ABG_fNum'	=		%f\n\n", *(&ABG_fNum));

	ABG_ptr = &ABG_fNum;

	printf("\n\n");
	printf("******** After ABG_ptr = &ABG_fNum *********\n\n");
	printf("Value Of 'ABG_fNum'		=		%f\n\n", ABG_fNum);
	printf("Address Of 'ABG_fNum'		=		%p\n\n", &ABG_ptr);
	printf("Value At Address Of 'ABG_fNum'	=		%f\n\n", *ABG_ptr);

	return(0);
}