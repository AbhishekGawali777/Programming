#include <stdio.h>


int main(void)
{
	int ABG_iArray[] = {10, 20, 30, 40, 50, 60, 70};
	int ABG_IntSize;
	int ABG_iArraySize;
	int ABG_iArrayNumElements;

	float ABG_fArray[] = { 1.2f, 2.3f, 3.4f, 4.5f, 5.6f, 6.7f, 7.8f };
	int ABG_FloatSize;
	int ABG_fArraySize;
	int ABG_fArrayNumElements;

	char ABG_cArray[] = { 'A', 'S', 'T', 'R','O', 'M', 'E', 'D', 'I', 'C', 'O', 'M','P'};
	int ABG_CharSize;
	int ABG_cArraySize;
	int ABG_cArrayNumElements;

	printf("\n\n");

	/***** ABG_iArray[] *****/

	printf("Inline Initialization And Piece Meal Initialization Of Elements Of Array 'ABG_iArray' : \n\n");

	printf("ABG_iArray[0] (1st Element) : %d\n", ABG_iArray[0]);
	printf("ABG_iArray[1] (2nd Element) : %d\n", ABG_iArray[1]);
	printf("ABG_iArray[2] (3rd Element) : %d\n", ABG_iArray[2]);
	printf("ABG_iArray[3] (4th Element) : %d\n", ABG_iArray[3]);
	printf("ABG_iArray[4] (5th Element) : %d\n", ABG_iArray[4]);
	printf("ABG_iArray[5] (6th Element) : %d\n", ABG_iArray[5]);
	printf("ABG_iArray[6] (7th Element) : %d\n", ABG_iArray[6]);

	ABG_IntSize = sizeof(int);
	ABG_iArraySize = sizeof(ABG_iArray);
	ABG_iArrayNumElements = ABG_iArraySize / ABG_IntSize;

	printf("\nSize of Datatype int Is : %d\n", ABG_IntSize);
	printf("Number Of Elements In 'ABG_iArray[]' Is : %d\n", ABG_iArrayNumElements);
	printf("Size of Array 'ABG_iArray[]' (%d Elements * %d bytes)Is : %d\n", ABG_iArrayNumElements, ABG_IntSize, ABG_iArraySize);
	
	/***** ABG_fArray[] *****/

	printf("Inline Initialization And Piece Meal Initialization Of Elements Of Array 'ABG_fArray' : \n\n");

	printf("ABG_fArray[0] (1st Element) : %f\n", ABG_fArray[0]);
	printf("ABG_fArray[1] (2nd Element) : %f\n", ABG_fArray[1]);
	printf("ABG_fArray[2] (3rd Element) : %f\n", ABG_fArray[2]);
	printf("ABG_fArray[3] (4th Element) : %f\n", ABG_fArray[3]);
	printf("ABG_fArray[4] (5th Element) : %f\n", ABG_fArray[4]);
	printf("ABG_fArray[5] (6th Element) : %f\n", ABG_fArray[5]);
	printf("ABG_fArray[6] (7th Element) : %f\n", ABG_fArray[6]);

	ABG_FloatSize = sizeof(float);
	ABG_fArraySize = sizeof(ABG_fArray);
	ABG_fArrayNumElements = ABG_fArraySize / ABG_FloatSize;

	printf("\nSize of Datatype 'float' Is : %d\n", ABG_FloatSize);
	printf("Number Of Elements In 'ABG_fArray[]' Is : %d\n", ABG_fArrayNumElements);
	printf("Size of Array 'ABG_fArray[]' (%d Elements * %d bytes)Is : %d\n", ABG_fArrayNumElements, ABG_FloatSize, ABG_fArraySize);


	/***** ABG_cArray[] *****/

	printf("Inline Initialization And Piece Meal Initialization Of Elements Of Array 'ABG_cArray' : \n\n");

	printf("ABG_iArray[0] (1st Element)   : %c\n", ABG_cArray[0]);
	printf("ABG_iArray[1] (2nd Element)   : %c\n", ABG_cArray[1]);
	printf("ABG_iArray[2] (3rd Element)   : %c\n", ABG_cArray[2]);
	printf("ABG_iArray[3] (4th Element)   : %c\n", ABG_cArray[3]);
	printf("ABG_iArray[4] (5th Element)   : %c\n", ABG_cArray[4]);
	printf("ABG_iArray[5] (6th Element)   : %c\n", ABG_cArray[5]);
	printf("ABG_iArray[6] (7th Element)   : %c\n", ABG_cArray[6]);
	printf("ABG_iArray[7] (8th Element)   : %c\n", ABG_cArray[7]);
	printf("ABG_iArray[8] (9th Element)   : %c\n", ABG_cArray[8]);
	printf("ABG_iArray[9] (10th Element)  : %c\n", ABG_cArray[9]);
	printf("ABG_iArray[10] (11th Element) : %c\n", ABG_cArray[10]);
	printf("ABG_iArray[11] (12th Element) : %c\n", ABG_cArray[11]);
	printf("ABG_iArray[12] (13th Element) : %c\n", ABG_cArray[12]);

	ABG_CharSize = sizeof(char);
	ABG_cArraySize = sizeof(ABG_cArray);
	ABG_cArrayNumElements = ABG_cArraySize / ABG_CharSize;

	printf("\nSize of Datatype 'char' Is : %d\n", ABG_CharSize);
	printf("Number Of Elements In 'ABG_cArray[]' Is : %d\n", ABG_cArrayNumElements);
	printf("Size of Array 'ABG_cArray[]' (%d Elements * %d bytes)Is : %d\n", ABG_cArrayNumElements, ABG_CharSize, ABG_cArraySize);

	return(0);
}