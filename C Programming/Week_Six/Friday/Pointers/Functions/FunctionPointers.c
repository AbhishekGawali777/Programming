#include <stdio.h>

int main(void)
{
	// Function Declarations

	int ABG_AddIntegers(int, int);
	int ABG_SubtractIntegers(int, int);
	float ABG_AddFloats(float,float);

	// Variable Declarations

	typedef int(*ABG_lpfnIntegers)(int, int);
	ABG_lpfnIntegers ABG_pAddIntegers = NULL;
	ABG_lpfnIntegers ABG_pSubtractIntegers = NULL;

	typedef float(*ABG_lpfnAddFloat)(float, float);
	ABG_lpfnAddFloat ABG_pAddFloats = NULL;

	int ABG_iAnswer = 0;
	float ABG_fAnswer = 0;

	// Code 

	ABG_pAddIntegers = ABG_AddIntegers;
	ABG_iAnswer = ABG_pAddIntegers(10, 20);
	printf("\n\n");
	printf("Sum Of Integers: \t%d", ABG_iAnswer);

	ABG_pSubtractIntegers = ABG_SubtractIntegers;
	ABG_iAnswer = ABG_pSubtractIntegers(487, 146);
	printf("\n\n");
	printf("Subtraction Of Integers: \t%d", ABG_iAnswer);

	ABG_pAddFloats= ABG_AddFloats;
	ABG_fAnswer = ABG_pAddFloats(68.14f, 73.21f);
	printf("\n\n");
	printf("Sum Of Floats-Point Numbers: \t%f", ABG_fAnswer);

	printf("\n\n");

	return(0);
}

int ABG_AddIntegers(int ABG_iNum1, int ABG_iNum2)
{
	return(ABG_iNum1 + ABG_iNum2);
}

int ABG_SubtractIntegers(int ABG_iNum1, int ABG_iNum2)
{
	return(ABG_iNum1 - ABG_iNum2);
}

float ABG_AddFloats(float ABG_fNum1, float ABG_fNum2)
{
	return(ABG_fNum1 + ABG_fNum2);
}