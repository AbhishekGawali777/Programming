#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE* pFile = NULL;

	if (fopen_s(&pFile, "LogFile.txt", "w") != 0)
	{
		printf("Cannot Create Desired File...!!!\n\n");
		exit(0);
	}

	fprintf_s(pFile, "India Is My Country.\n");

	fclose(pFile);

	pFile = NULL;

	return(0);
}