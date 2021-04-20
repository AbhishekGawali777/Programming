#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#include<string.h>

#define SUCCESS		1
#define FAILURE		2
#define ARR_SIZE	10

struct dynamic_array
{
	size_t size;
	int* p_arr;
};


struct dynamic_array* create_dynamic_array(int size);
int get_element_at_index(struct dynamic_array* p_dynamic_array, size_t index, int* p_element);
int set_element_at_index(struct dynamic_array* p_dynamic_array, size_t index, int new_element);
int destroy_dynamic_array(struct dynamic_array* p_dynamic_array);

#endif //	__DYNAMIC_ARRAY_H__
