#include <stdio.h>

typedef int ABG_INT;

int main(void)
{
	ABG_INT ABG_Add(ABG_INT, ABG_INT);

	typedef int ABG_INT;
	typedef char ABG_CHAR;
	typedef float ABG_FLOAT;
	typedef double ABG_DOUBLE;

	/********* LIKE WIN32 SDK*********/

	typedef unsigned int UINT;
	typedef UINT HWND;
	typedef HWND HANDLE;
	typedef HANDLE HINSTANCE;

	ABG_INT ABG_iNum = 10;
	ABG_INT ABG_iLoopCounter;
	ABG_INT ABG_iArray[] = { 9, 10, 12, 25, 75, 93, 87, 19, 26, 56 };

	ABG_FLOAT ABG_fNum = 22.16f;
	const ABG_FLOAT ABG_fPI = 3.1415f;

	ABG_CHAR ABG_cCh = 'A';
	ABG_CHAR ABG_cArray1[] = "Hello";
	ABG_CHAR ABG_cArray2[][20] = { "Real", "Time", "Rendering..!!!" };

	ABG_DOUBLE ABG_dNum = 12.458935;

	UINT uint = 1256;
	HWND hwnd = 456;
	HANDLE handle = 128;
	HINSTANCE hInstance = 367;

	printf("\n\n");
	printf("Type ABG_INT variable ABG_iNum = %d\n", ABG_iNum);
	printf("\n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < (sizeof(ABG_iArray) / sizeof(int)); ABG_iLoopCounter++)
	{
		printf("Type ABG_INT Array Variable  ABG_iArray[%d] = %d\n", ABG_iLoopCounter, ABG_iArray[ABG_iLoopCounter]);
	}
	printf("\n\n");

	printf("\n\n");

	printf("Type ABG_FLOAT Variable ABG_fNum = %f\n", ABG_fNum);
	printf("Type ABG_FLOAT Variable ABG_fPI = %f\n", ABG_fPI);

	printf("\n\n");
	printf("Type ABG_DOUBLE Variable ABG_dNum = %lf\n", ABG_dNum);

	printf("\n\n");
	printf("Type ABG_CHAR Variable ABG_cCh = %d\n", ABG_cCh);

	printf("\n\n");
	printf("Type ABG_CHAR Array Variable ABG_cArray1 = %s\n", ABG_cArray1);

	printf("\n\n");

	for (ABG_iLoopCounter = 0; ABG_iLoopCounter < (sizeof(ABG_cArray2) / sizeof(ABG_cArray2[0])); ABG_iLoopCounter++)
	{
		printf("%s\t", ABG_cArray2[ABG_iLoopCounter]);
	}
	
	printf("\n\n");
	printf("Type UINT Variable uint = %u\n\n", uint);
	printf("Type HWND Variable hwnd = %u\n\n", hwnd);
	printf("Type HANDLE Variable handle = %u\n\n", handle);
	printf("Type HINSTANCE Variable hInstance = %u\n\n", hInstance);

	ABG_INT x = 90;
	ABG_INT y = 30;
	ABG_INT ABG_iRet;

	ABG_iRet = Add(x, y);

	return(0);
}

ABG_INT Add(ABG_INT x, ABG_INT y)
{
	ABG_INT ABG_iResult;
	ABG_iResult = x + y;

	return(ABG_iResult);
}