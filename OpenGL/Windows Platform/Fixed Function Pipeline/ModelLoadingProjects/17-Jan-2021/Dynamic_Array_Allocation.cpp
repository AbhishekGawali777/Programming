
#include"Dynamic_Array_Allocation.h"

// Global Array Declaration

int Arr[5];

int main(void)
{
	// Code

	read_write_on_static_array();
	allocate_read_write_free_dynamic_array();

	return(EXIT_SUCCESS);
}

void read_write_on_static_array()
{
	// Lcoal Variable Declaration

	int i;

	// Code

	/* Write On Static Array */

	for(i = 0; i < 5; ++i)
	{
		Arr[i] = (i + 1) * 10;
	}

	/* Read From static array */

	for(i = 0; i < 5; ++i)
		printf("Arr[%d] = %d\n", i, Arr[i]);
}


void allocate_read_write_free_dynamic_array()
{
	/* Local Varoable Declarations */

	int i, n;
	int* p = NULL;

	// Code

	p = (int*)malloc(5 * sizeof(int));

	if(NULL == p)
	{
		printf("Unable to allocate Memory\n");
		exit(EXIT_FAILURE);
	}

	/* Initilize all element of array by 0 */

	memset(p, 0, 5 * sizeof(int));

	/* Write */

	for(i = 0; i < 5; ++i)
	{
		p[i] = (i + 1) * 100;
		//*(p + i) = (i + 1) * 100;
	}

	/* Read */

	for(i = 0; i < 5; ++i)
	{
		printf("*(p + %d) = %d\n", i, *(p+i));
	}

	/* Free */

	free(p);
	p = NULL;
}
