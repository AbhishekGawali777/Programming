#include <stdio.h>

#define ABG_STEP		20
#define ABG_LOWERLIMIT	0
#define ABG_UPPERLIMIT	300

int main(int argc, char* argv[])
{
	int ABG_Fahrenheit = ABG_LOWERLIMIT;

	printf("\n--------------- Fahrenheit To Celcius Table ---------------\n\n");
	void ABG_FahrenheitToCelcius(int);

	ABG_FahrenheitToCelcius(ABG_Fahrenheit);

	return(0);
}

void ABG_FahrenheitToCelcius(int ABG_FormalFahrenheit)
{
	int ABG_Celcius = -1;

	if (-1 == ABG_FormalFahrenheit)
		return;

	ABG_Celcius = 5 * (ABG_FormalFahrenheit - 32) / 9;
	printf("\t\t%d\t\t%d\n", ABG_FormalFahrenheit, ABG_Celcius);

	if (ABG_FormalFahrenheit <= ABG_UPPERLIMIT)
		ABG_FahrenheitToCelcius(ABG_FormalFahrenheit + ABG_STEP);
}