
#include "head.h"

#define SIZE10 (1024)
#define SIZE16 (65536)
#define SIZE26 (262144)
#define SIZE32 (4294967296)
#define SIZE42 (4398046511104)

typedef struct CodeBox
{
	char d[1024];
} CodeBox;

typedef struct CodeBoxTable
{
	size_t top;
	VoidNode* d;

} CodeBoxTable;

static CodeBoxTable* head;

/*
* CodeBox table을 반환
*/
CodeBoxTable* CodeBoxHead()
{
	return head;
}

/*
* CodeBox table의 주소를 반환
*/
CodeBoxTable** CodeBoxHeadPointer()
{
	return &head;
}

/*
* CodeBox table의 시작
*/
ErrorCode CodeBoxBegin()
{
	
	if (!CodeBoxHead())
	{
		ErrorCode error;
		CodeBoxTable** table = CodeBoxHeadPointer();
		error = newMalloc(table, sizeof(CodeBoxTable));
		if (error != ERROR_NONE) return error;
		
		error = newVoidNode(&(*table)->d);
		if (error != ERROR_NONE) return error;
		
		(*table)->top = 0;
	}

	return ERROR_NONE;
}

size_t getCodeBoxTop()
{
	return CodeBoxHead()->top;
}

/*
* CodeBox에 데이터 추가
* char 형태로 저장
*/
ErrorCode setCodeBox(char d)
{
	ErrorCode error;
	if (!CodeBoxHead()) // 테이블이 있는지 확인
	{
		error = CodeBoxBegin(); // 테이블이 없으면 생성
		if (error != ERROR_NONE) return error;
	}

	CodeBoxTable* headTable = CodeBoxHead(); // 1차 테이블은 여기 있음
	CodeBoxTable** headTablePointer = CodeBoxHeadPointer();
	VoidNode* table; // 2차 테이블 선언

	error = getValNode(headTable->d, headTable->top / SIZE26, &table); // 2차 테이블 저장
	if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		error = newVoidNode(&table);
		if (error != ERROR_NONE) return error;

		error = newValNode(&(*headTablePointer)->d, headTable->top / SIZE26, table);
		if (error != ERROR_NONE) return error;

	}
	else if (error != ERROR_NONE) return error;

	CodeBox* Node; // 3차 테이블 선언

	error = getValNode(table, headTable->top % SIZE26 / SIZE10, &Node);
	if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		error = newMalloc(&Node, sizeof(CodeBox)); // 3차 테이블 메모리 할당
		if (error != ERROR_NONE) return error;

		error = newValNode(&table, headTable->top % SIZE26 / SIZE10, Node); // 3차 테이블 저장

		if (error != ERROR_NONE) return error;

	}
	else if (error != ERROR_NONE) return error;

	Node->d[headTable->top % SIZE10] = d; // 3차 테이블의 값에 저장
	headTable->top++; // 다음 index로 넘김



	return ERROR_NONE;
}

/*
* CodeBox의 데이터 읽기
* char 형태로 읽음
*/
ErrorCode getCodeBox(size_t index, char* d)
{
	ErrorCode error;
	if (!CodeBoxHead()) return ERROR_NULL_POINTER; // 테이블이 없으면 에러

	if (index < 0 || SIZE42 < index) return ERROR_INVALID_INDEX; // 인덱스가 밖이어도 에러

	CodeBoxTable* Table = CodeBoxHead(); // 1차 테이블은 여기 있음
	VoidNode* table; // 2차 테이블 선언

	error = getValNode(Table->d, index / SIZE26, &table); // 2차 테이블 읽기
	if (error != ERROR_NONE) return error;

	CodeBox* Node; // 3차 테이블 선언
	error = getValNode(table, index % SIZE26 / SIZE10, &Node); // 3차 테이블 읽기
	if (error != ERROR_NONE) return error;

	*d = Node->d[index % SIZE10]; // 3차 테이블의 값을 읽기
	return ERROR_NONE;
}

/*
* CodeBoxTable의 End, 해당 테이블을 제거함
*/
ErrorCode CodeBoxTableEnd()
{
	ErrorCode error = ERROR_NONE;
	CodeBoxTable** Table = CodeBoxHeadPointer();
	if (!*Table) return ERROR_NULL_POINTER;

	VoidNode** table = &(*Table)->d;
	for (size_t index = 0; index < (*Table)->top / SIZE26 + 1; index++) // 2차 테이블 제거 시퀀스
	{
		//printf("%LL %p %LL", index, *Table, (*Table)->top);
		VoidNode** node;
		error = getValNodePointer(*table, index, &node); // 2차 테이블 가져오기
		if (error != ERROR_NONE) continue;

		error = freeValNode(node); // 2차 테이블 제거

	}
	error = freeValNode(table); // 1차 테이블 제거
	free(*Table); // 테이블 제거
	*Table = NULL;

	return error;
}