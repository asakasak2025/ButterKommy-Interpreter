
#include "head.h"

/*
* VoidNode�� �����մϴ�.
* �ش� VoidNode�� table �Դϴ�.
* ��ü���� VoidNode talbe�� �����Ҵ� �ϴ� �뵵�� ���ϴ�.
*/
ErrorCode newVoidNode(VoidNode** node) 
{
	*node = calloc(1, sizeof(VoidNode));
	if (!*node) return ERROR_MEMORY_ALLOC_FAIL;
	return ERROR_NONE;
}

/*
* VoidNode table�� block�� �߰��մϴ�
*/
ErrorCode newValNode(VoidNode** voidNode, int index, void* block) 
{

	if (256 * 256 <= index || index < 0 ) // ��ȿ �ε����� �ƴ�
	{
		return ERROR_INVALID_INDEX;
	}

	if (!*voidNode) // 1�� VoidNode talbe�� �������� ����
	{
		ErrorCode error = newVoidNode(voidNode);
		if (error != ERROR_NONE) return error;
	}

	if (!(*voidNode)->data[index / 256]) // 2�� VoidNode�� �������� ����
	{
		ErrorCode error = newVoidNode( &(*voidNode)->data[index / 256] );
		if (error != ERROR_NONE) return error;
	}
	
	{
		VoidNode* get = (*voidNode)->data[index / 256];
		if (!get->data[index % 256]) get->data[index % 256] = block;
		else return ERROR_POINTER_OVERLAP; // 3�� Block�� ������
	}
	
	return ERROR_NONE;

}

/*
* VoidNode talbe�� block�� node�� �Ҵ��մϴ�.
* ������ block�� ���� ���·� ��ȯ�ؼ� ������ּ���.
*/
ErrorCode getValNode(VoidNode* voidNode, int index, void** node) 
{
	if (256 * 256 <= index || index < 0) return ERROR_INVALID_INDEX; // ��ȿ �ε����� �ƴ�
	if (!voidNode) return ERROR_NULL_POINTER; // 1�� VoidNode talbe pointer�� �������� ����
	if (!voidNode->data[index / 256]) return ERROR_NULL_POINTER; // 2�� VoidNode�� �������� ����
	
	VoidNode* get = voidNode->data[index / 256];
	if (get->data[index % 256]) *node = get->data[index % 256];
	else return ERROR_INVALID_VAL; // 3�� Block�� �������� ����
	return ERROR_NONE;
}

/*
* VoidNode talbe�� block�� �ּҸ� node�� �Ҵ��մϴ�.
*/
ErrorCode getValNodePointer(VoidNode* voidNode, int index, void*** node)
{
	if (256 * 256 <= index || index < 0) return ERROR_INVALID_INDEX; // ��ȿ �ε����� �ƴ�
	if (!voidNode) return ERROR_NULL_POINTER; // 1�� VoidNode talbe pointer�� �������� ����
	if (!voidNode->data[index / 256]) return ERROR_NULL_POINTER; // 2�� VoidNode�� �������� ����

	VoidNode* get = voidNode->data[index / 256];
	if (get->data[index % 256]) *node = &get->data[index % 256];
	else return ERROR_INVALID_VAL; // 3�� Block�� �������� ����
	return ERROR_NONE;
}

/*
* VoidNode talbe�� �����մϴ�.
* ���� EvnetNode�� ���ŵɶ� ȣ��˴ϴ�.
*/
ErrorCode freeValNode(VoidNode** voidNode) 
{
	if (*voidNode) // 1�� VoidNode table�� ����
	{
		for (int index = 0; index < 1; index++) // 2�� VoidNode�� ����
		{
			VoidNode* get = (*voidNode)->data[index];
			if (get)
			{
				for (int index = 0; index < 256; index++) // 3�� Block�� ����
				{
					if (get->data[index]) free(get->data[index]);
				}
				free(get); // 2�� VoidNode�� �ǻ���
			}
		}
		free(*voidNode); // 1�� VoidNode table�� �ǻ���
		*voidNode = NULL; // �������� ����
	}
	else return ERROR_NULL_POINTER; // 1�� VoidNode talbe pointer�� �������� ����
	return ERROR_NONE;
}