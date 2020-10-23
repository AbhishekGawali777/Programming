#include <stdio.h>

// MACRO Declaration

#define ABG_STEP		20
#define ABG_UPPERLIMIT	300
#define ABG_LOWERLIMIT	0

// Function Signature / Prototype / Declaration

int ABG_FahrenheitToCelcius(int);


int main(int argc, char* argv[])
{

	int ABG_Fahrenheit = -1;

	printf("----------------------- Fahrenheit To Celcius Table ---------------------\n\n");

	for (ABG_Fahrenheit = ABG_LOWERLIMIT; ABG_Fahrenheit <= ABG_UPPERLIMIT; ABG_Fahrenheit = ABG_Fahrenheit + ABG_STEP)
	{
		printf("\t\t%d\t\t%d\n", ABG_Fahrenheit, ABG_FahrenheitToCelcius(ABG_Fahrenheit));
	}

	return(0);
}

//Function Definition

int ABG_FahrenheitToCelcius(int ABG_FormalFahrenheit)
{
	int ABG_LocalCelcius = -1;

	if (ABG_FormalFahrenheit == -1)
	{
		return -1;
	}

	ABG_LocalCelcius = 5 * (ABG_FormalFahrenheit - 32) / 9;

	return(ABG_LocalCelcius);
}