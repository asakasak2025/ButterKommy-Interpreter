
#include "head.h"



/*
* PointNodeTable�� ������
*/
static VoidNode* PointNodeTable;


/*
* PointNode�� ������
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
* PointNode�� �Ҵ��մϴ�
* size_t ���� �޾Ƽ� �����մϴ�
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
* PointNode�� ���� �����ɴϴ�
* size_t ���·� �����ɴϴ�
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
* PointNodeTable�� �����ϴ�.
*/
ErrorCode PointNodeTableEnd()
{
	ErrorCode error = freeValNode(&PointNodeTable);
	return error;
}