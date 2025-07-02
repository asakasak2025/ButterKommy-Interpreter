
// 이런 작은 객체를 만들어야 하려나?

#include "head.h"

/*
* array<int>를 만드는 함수
*/
ErrorCode newIntArray(IntArray** data, size_t count, size_t size)
{
	ErrorCode error;

	if (*data) return ERROR_POINTER_OVERLAP;

	error = newMalloc((void**)data, sizeof(IntArray));
	if (!*data) return ERROR_MEMORY_ALLOC_FAIL;
	if (error != ERROR_NONE) return error;
	

	if (size <= count) size += count;

	error = newCalloc((void**) & (*data)->d, size, sizeof(int));
	if (error != ERROR_NONE) return error;

	(*data)->count = count;
	(*data)->size = size;

	return ERROR_NONE;
}

/*
* array<int>에서 값의 포인터를 꺼내는 함수
*/
ErrorCode getIntArrayDataPointer(IntArray* array, size_t index, int** d)
{
	ErrorCode error;
	
	if (!array) return ERROR_NULL_POINTER;
	else
	{
		if ((array)->size <= (array)->count)
		{
			error = newRealloc( (void**)(& array->d), (array)->size *= 2);
			if (error != ERROR_NONE) return error;
		}

		if (index >= (array)->count) return ERROR_INVALID_INDEX;
		else
		{
			*d = &array->d[index];
		}
	}

	return ERROR_NONE;
}

/*
* array<int>에서 값을 꺼내는 함수
*/
ErrorCode getIntArrayData(IntArray* array, size_t index, int* d)
{
	int* data;
	ErrorCode error = getIntArrayDataPointer(array, index, &data);
	if (error != ERROR_NONE) return error;
	if (data) *d = *data;
	else return ERROR_NULL_POINTER;
	return ERROR_NONE;
}

/*
* array<int>에서 값을 저장하는 함수
*/
ErrorCode setIntArrayData(IntArray* array, size_t index, int d)
{
	int* data;
	ErrorCode error = getIntArrayDataPointer(array, index, &data);
	if (error != ERROR_NONE) return error;
	if (data) *data = d;
	else return ERROR_NULL_POINTER;
	return ERROR_NONE;
}