
#include "head.h"



/*
* PointNodeTable의 저장점
*/
static VoidNode* PointNodeTable;


/*
* PointNode의 시작점
*/
ErrorCode PointNodeTableBegin()
{
	if (!PointNodeTable)
	{
		ErrorCode error;
		error = newVoidNode(&PointNodeTable);
		return error;
	}
	return ERROR_NONE;
}


/*
* PointNode를 할당합니다
* size_t 값을 받아서 저장합니다
*/
ErrorCode setPointNode(int index, size_t point)
{
	ErrorCode error;
	if (!PointNodeTable)
	{
		error = PointNodeTableBegin();
		if (error != ERROR_NONE) return error;
	}

	if (PointNodeTable)
	{
		PointNode* node;
		error = newMalloc(&node, sizeof(PointNode));
		if (error != ERROR_NONE) return error;

		node->point = point;
		error = newValNode(&PointNodeTable, index, node);
		if (error != ERROR_NONE) return error;
	}
	else return ERROR_NULL_POINTER;

	return ERROR_NONE;

}

/*
* PointNode의 값을 가져옵니다
* size_t 형태로 가져옵니다
*/
ErrorCode getPointNode(int index, size_t* point)
{
	if (!PointNodeTable) return ERROR_NULL_POINTER;
	else
	{
		ErrorCode error;
		PointNode* node;
		error = getValNode(PointNodeTable, index, &node);
		if (error != ERROR_NONE) return error;

		*point = node->point;
	}
	return ERROR_NONE;
}

/*
* PointNodeTable를 끝냅니다.
*/
ErrorCode PointNodeTableEnd()
{
	ErrorCode error = freeValNode(&PointNodeTable);
	return error;
}