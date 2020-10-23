#include <stdio.h>

int main(void)
{
	int ABG_iLoopCounter;

	int ABG_iArray[] = { 10, 20, 30, 40, 50, 60, 70 };
	int ABG_IntSize;
	int ABG_iArraySize;
	int ABG_iArrayNumElements;

	float ABG_fArray[] = { 1.2f, 2.3f, 3.4f, 4.5f, 5.6f, 6.7f, 7.8f };
	int ABG_FloatSize;
	int ABG_fArraySize;
	int ABG_fArrayNumElements;

	char ABG_cArray[] = { 'A', 'S', 'T', 'R','O', 'M', 'E', 'D', 'I', 'C', 'O', 'M','P' };
	int ABG_CharSize;
	int ABG_cArraySize;
	int ABG_cArrayNumElements;

	printf("\n\n");

	/***** ABG_iArray[] *****/

	printf("Inline Initialization And 'for' Loop Initialization Of Elements Of Array 'ABG_iArray' : \n\n");

	ABG_IntSize = sizeof(int);
	ABG_iArraySize = sizeof(ABG_iArray);
	ABG_iArrayNumElements = ABG_iArraySize / ABG_IntSize;

	for(ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_iArraySize / ABG_IntSize; ABG_iLoopCounter++)
		printf("ABG_iArray[%d] (%d Element) : %d\n",ABG_iLoopCounter, ABG_iLoopCounter + 1, ABG_iArray[ABG_iLoopCounter]);

	printf("\nSize of Datatype int Is : %d\n", ABG_IntSize);
	printf("Number Of Elements In 'ABG_iArray[]' Is : %d\n", ABG_iArrayNumElements);
	printf("Size of Array 'ABG_iArray[]' (%d Elements * %d bytes)Is : %d\n", ABG_iArrayNumElements, ABG_IntSize, ABG_iArraySize);
	
	/***** ABG_fArray[] *****/
	
	printf("Inline Initialization And 'for' Loop Initialization Of Elements Of Array 'ABG_fArray' : \n\n");

	ABG_FloatSize = sizeof(float);
	ABG_fArraySize = sizeof(ABG_fArray);
	ABG_fArrayNumElements = ABG_fArraySize / ABG_FloatSize;

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_fArraySize / ABG_FloatSize; ABG_iLoopCounter++)
		printf("ABG_fArray[%d] (%d Element) : %f\n", ABG_iLoopCounter, ABG_iLoopCounter + 1, ABG_fArray[ABG_iLoopCounter]);
	
	printf("\nSize of Datatype 'float' Is : %d\n", ABG_FloatSize);
	printf("Number Of Elements In 'ABG_fArray[]' Is : %d\n", ABG_fArrayNumElements);
	printf("Size of Array 'ABG_fArray[]' (%d Elements * %d bytes)Is : %d\n", ABG_fArrayNumElements, ABG_FloatSize, ABG_fArraySize);

	/***** ABG_cArray[] *****/

	printf("Inline Initialization And Piece Meal Initialization Of Elements Of Array 'ABG_cArray' : \n\n");

	ABG_CharSize = sizeof(char);
	ABG_cArraySize = sizeof(ABG_cArray);
	ABG_cArrayNumElements = ABG_cArraySize / ABG_CharSize;

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < ABG_cArraySize; ABG_iLoopCounter++)
		printf("ABG_fArray[%d] (%d Element) : %c\n", ABG_iLoopCounter, ABG_iLoopCounter + 1, ABG_cArray[ABG_iLoopCounter]);


	printf("\nSize of Datatype 'char' Is : %d\n", ABG_CharSize);
	printf("Number Of Elements In 'ABG_cArray[]' Is : %d\n", ABG_cArrayNumElements);
	printf("Size of Array 'ABG_cArray[]' (%d Elements * %d bytes)Is : %d\n", ABG_cArrayNumElements, ABG_CharSize, ABG_cArraySize);


	return(0);
}