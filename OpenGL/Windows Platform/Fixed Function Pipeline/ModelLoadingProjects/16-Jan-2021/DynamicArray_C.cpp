
// Header Files

#include"DynamicArray.h"

// main()

int main(void)
{
	// Local Variable Declaration

	int i;
	int data;
	size_t return_value;
	struct dynamic_array* p_dynamic_array = NULL;

	// Code

	p_dynamic_array = create_dynamic_array(ARR_SIZE);

	for (i = 0; i < ARR_SIZE; ++i)
	{
		return_value = set_element_at_index(p_dynamic_array, i, (i + 1) * 10);
		assert(SUCCESS == return_value);
	}

	for (i = 0; i < ARR_SIZE; ++i)
	{
		return_value = get_element_at_index(p_dynamic_array, i, &data);
		assert(SUCCESS == return_value);
		printf("Data at index : %d is %d\n", i, data);
	}

	return_value = destroy_dynamic_array(p_dynamic_array);
	assert(SUCCESS == return_value);
	p_dynamic_array = NULL;

	return(EXIT_SUCCESS);
}

struct dynamic_array* create_dynamic_array(int nSize)
{
	// Local variable declaration

	struct dynamic_array* p_dynamic_array = NULL;

	// Code

	if (nSize < 0)
	{
		printf("Bad Array Size\n");
		exit(EXIT_FAILURE);
	}

	p_dynamic_array = (struct dynamic_array*)malloc(sizeof(struct dynamic_array) * nSize);

	if (NULL == p_dynamic_array)
	{
		printf("Failed To allocate memory\n");
		exit(EXIT_FAILURE);
	}

	p_dynamic_array->size = nSize;
	p_dynamic_array->p_arr = (int*)malloc(sizeof(int) * nSize);

	memset(p_dynamic_array->p_arr, 0, sizeof(int) * nSize);

	if (NULL == p_dynamic_array->p_arr)
	{
		printf("Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	return(p_dynamic_array);
}

int set_element_at_index(struct dynamic_array* p_dynamic_array, size_t index, int new_element)
{
	// Code

	if (index < 0 || index >= p_dynamic_array->size)
		return(FAILURE);

	p_dynamic_array->p_arr[index] = new_element;
	return(SUCCESS);
}

int get_element_at_index(struct dynamic_array* p_dynamic_array, size_t index, int* p_data)
{
	// Code

	if (index < 0 || index >= p_dynamic_array->size)
		return(FAILURE);

	*p_data = p_dynamic_array->p_arr[index];
	return(SUCCESS);
}

int destroy_dynamic_array(struct dynamic_array* p_dynamic_array)
{
	// Code

	free(p_dynamic_array->p_arr);
	free(p_dynamic_array);

	return(SUCCESS);
}
