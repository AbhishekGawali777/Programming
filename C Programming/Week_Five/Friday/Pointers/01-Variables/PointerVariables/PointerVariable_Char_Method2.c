#include <stdio.h>

int main(void)
{
	char ABG_cCh;
	char *ABG_ptr = NULL;

	ABG_cCh = 'V';

	printf("\n\n");
	printf("******** Before ABG_ptr = &ABG_cCh *********\n\n");
	printf("Value Of 'ABG_cCh'		=		%c\n\n", ABG_cCh);
	printf("Address Of 'ABG_cCh'		=		%p\n\n", &ABG_cCh);
	printf("Value At Address Of 'ABG_cCh'	=		%c\n\n", *(&ABG_cCh));

	ABG_ptr = &ABG_cCh;

	printf("\n\n");
	printf("******** After ABG_ptr = &ABG_cCh *********\n\n");
	printf("Value Of 'ABG_cCh'		=		%c\n\n", ABG_cCh);
	printf("Address Of 'ABG_cCh'		=		%p\n\n", &ABG_ptr);
	printf("Value At Address Of 'ABG_cCh'	=		%c\n\n", *ABG_ptr);

	return(0);
}