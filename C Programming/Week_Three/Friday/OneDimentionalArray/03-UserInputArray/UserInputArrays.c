#include <stdio.h>

#define INT_ARRAY_NUM_ELEMENTS		5
#define FLOAT_ARRAY_NUM_ELEMENTS	5
#define CHAR_ARRAY_NUM_ELEMENTS		13


int main(void)
{
	int ABG_iArray[INT_ARRAY_NUM_ELEMENTS];
	float ABG_fArray[FLOAT_ARRAY_NUM_ELEMENTS];
	char ABG_cArray[CHAR_ARRAY_NUM_ELEMENTS];

	int ABG_iLoopCounter, ABG_iNumber;

	printf("\n\n");
	
	printf("Enter Elements For 'Integer' Array : \n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < INT_ARRAY_NUM_ELEMENTS; ABG_iLoopCounter++)
		scanf("%d", &ABG_iArray[ABG_iLoopCounter]);
	
	printf("\n\n");
	
	printf("Enter Elements For 'Floating-Point' Array : \n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < FLOAT_ARRAY_NUM_ELEMENTS; ABG_iLoopCounter++)
		scanf("%f", &ABG_fArray[ABG_iLoopCounter]);
	
	printf("\n\n");
	
	printf("Enter Elements For 'Character' Array : \n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < CHAR_ARRAY_NUM_ELEMENTS; ABG_iLoopCounter++)
	{
		ABG_cArray[ABG_iLoopCounter] = getch();
		printf("%c\n", ABG_cArray[ABG_iLoopCounter]);
	}

	printf("\n\n");
	
	printf("Integer Array Entered By You : \n\n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < INT_ARRAY_NUM_ELEMENTS; ABG_iLoopCounter++)
		printf("%d\n", ABG_iArray[ABG_iLoopCounter]);
	
	printf("\n\n");
	
	printf("Floating-Point Array Entered By You : \n\n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < FLOAT_ARRAY_NUM_ELEMENTS; ABG_iLoopCounter++)
		printf("%f\n", ABG_fArray[ABG_iLoopCounter]);
	
	printf("\n\n");

	printf("Character Array Entered By You : \n\n");
	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < CHAR_ARRAY_NUM_ELEMENTS; ABG_iLoopCounter++)
		printf("%c\n", ABG_cArray[ABG_iLoopCounter]);

	return(0);	
}