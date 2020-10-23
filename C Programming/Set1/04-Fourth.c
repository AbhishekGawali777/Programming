#include <stdio.h>

int main(int argc, char* argv[])
{
	int ABG_Year = 0;

	//scanf("Please Enter Integer Value : ");

	printf("Please Enter Integer Value :");

	scanf("%d", &ABG_Year);

	if ((ABG_Year % 4 == 0) && (ABG_Year % 100 == 0) || (ABG_Year % 400 == 0))
	{
		printf("%d Is A Leap Year.\n", ABG_Year);
	}
	else
	{
		printf("%d Is Not a Leap Year.\n", ABG_Year);
	}

	return(0);
}