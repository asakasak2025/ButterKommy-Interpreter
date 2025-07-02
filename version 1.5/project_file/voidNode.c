
#include "head.h"

/*
* VoidNode를 생성합니다.
* 해당 VoidNode는 table 입니다.
* 객체에서 VoidNode talbe을 동적할당 하는 용도로 씁니다.
*/
ErrorCode newVoidNode(VoidNode** node) 
{
	*node = calloc(1, sizeof(VoidNode));
	if (!*node) return ERROR_MEMORY_ALLOC_FAIL;
	return ERROR_NONE;
}

/*
* VoidNode table에 block을 추가합니다
*/
ErrorCode newValNode(VoidNode** voidNode, int index, void* block) 
{

	if (256 * 256 <= index || index < 0 ) // 유효 인덱스가 아님
	{
		return ERROR_INVALID_INDEX;
	}

	if (!*voidNode) // 1차 VoidNode talbe가 존재하지 않음
	{
		ErrorCode error = newVoidNode(voidNode);
		if (error != ERROR_NONE) return error;
	}

	if (!(*voidNode)->data[index / 256]) // 2차 VoidNode가 존재하지 않음
	{
		ErrorCode error = newVoidNode( &(*voidNode)->data[index / 256] );
		if (error != ERROR_NONE) return error;
	}
	
	{
		VoidNode* get = (*voidNode)->data[index / 256];
		if (!get->data[index % 256]) get->data[index % 256] = block;
		else return ERROR_POINTER_OVERLAP; // 3차 Block이 존재함
	}
	
	return ERROR_NONE;

}

/*
* VoidNode talbe의 block을 node에 할당합니다.
* 가져온 block은 원래 형태로 변환해서 사용해주세요.
*/
ErrorCode getValNode(VoidNode* voidNode, int index, void** node) 
{
	if (256 * 256 <= index || index < 0) return ERROR_INVALID_INDEX; // 유효 인덱스가 아님
	if (!voidNode) return ERROR_NULL_POINTER; // 1차 VoidNode talbe pointer가 존재하지 않음
	if (!voidNode->data[index / 256]) return ERROR_NULL_POINTER; // 2차 VoidNode가 존재하지 않음
	
	VoidNode* get = voidNode->data[index / 256];
	if (get->data[index % 256]) *node = get->data[index % 256];
	else return ERROR_INVALID_VAL; // 3차 Block가 존재하지 않음
	return ERROR_NONE;
}

/*
* VoidNode talbe의 block의 주소를 node에 할당합니다.
*/
ErrorCode getValNodePointer(VoidNode* voidNode, int index, void*** node)
{
	if (256 * 256 <= index || index < 0) return ERROR_INVALID_INDEX; // 유효 인덱스가 아님
	if (!voidNode) return ERROR_NULL_POINTER; // 1차 VoidNode talbe pointer가 존재하지 않음
	if (!voidNode->data[index / 256]) return ERROR_NULL_POINTER; // 2차 VoidNode가 존재하지 않음

	VoidNode* get = voidNode->data[index / 256];
	if (get->data[index % 256]) *node = &get->data[index % 256];
	else return ERROR_INVALID_VAL; // 3차 Block가 존재하지 않음
	return ERROR_NONE;
}

/*
* VoidNode talbe를 제거합니다.
* 보통 EvnetNode가 제거될때 호출됩니다.
*/
ErrorCode freeValNode(VoidNode** voidNode) 
{
	if (*voidNode) // 1차 VoidNode table의 삭제
	{
		for (int index = 0; index < 1; index++) // 2차 VoidNode의 삭제
		{
			VoidNode* get = (*voidNode)->data[index];
			if (get)
			{
				for (int index = 0; index < 256; index++) // 3차 Block의 삭제
				{
					if (get->data[index]) free(get->data[index]);
				}
				free(get); // 2차 VoidNode의 실삭제
			}
		}
		free(*voidNode); // 1차 VoidNode table의 실삭제
		*voidNode = NULL; // 다중제거 방지
	}
	else return ERROR_NULL_POINTER; // 1차 VoidNode talbe pointer가 존재하지 않음
	return ERROR_NONE;
}