#include <stdio.h>

#define ABG_STEP  20
#define ABG_LOWERLIMIT 0
#define ABG_UPPERLIMIT 300

int main(int argc, char* argv[])
{
	int ABG_Fahrenheit = -1;

	printf("---------------------- Fahrenheit to Celcius table ----------------------");

	for (ABG_Fahrenheit = ABG_LOWERLIMIT; ABG_Fahrenheit <= ABG_UPPERLIMIT; ABG_Fahrenheit += ABG_STEP)
	{
		printf("\t\t%3d\t\t%6.1f\n", ABG_Fahrenheit, (5.0 / 9.0) * (ABG_Fahrenheit - 32));
	}

}