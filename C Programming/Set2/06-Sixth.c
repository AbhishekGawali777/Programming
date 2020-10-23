#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_Step		= 20;
	int ABG_Celcius		= -1;
	int ABG_Fahrenheit	= -1;
	int ABG_UpperLimit	= 300;
	int ABG_LowerLimit	= 0;

	ABG_Fahrenheit = ABG_LowerLimit;

	printf("\n---------------- Fahrenheit To Celcius Table ---------------\n\n");

	while (ABG_Fahrenheit <= ABG_UpperLimit)
	{
		ABG_Celcius = 5 * (ABG_Fahrenheit - 32) / 9;

		printf("\t\t%d\t\t%d\n", ABG_Fahrenheit, ABG_Celcius);

		ABG_Fahrenheit = ABG_Fahrenheit + ABG_Step;
	}

	return(0);
}