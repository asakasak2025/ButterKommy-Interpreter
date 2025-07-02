
#include "head.h"

static struct
{
	int ParentMemoryRead;
} FileEvnet = {
		.ParentMemoryRead = 1,
};

/*
* 정수형 변수를 저장함
*/
typedef struct NumNode
{
	int data;
} NumNode;

/*
* 스트링 변수를 저장함
*/
typedef struct StrValNode
{
	char* d;
	size_t size;
	size_t len;
} StrNode;

/*
* EventPointStack 흐름을 관리하는 용도의 객체임
* Num과 Str테이블이 존재하며, 여기서 변수를 호출함
* 이벤트가 끝날시 저장된 Point로 이동함
* 정수형 Evnet 값은 이것이 어떤 명령어로 호출이 되었는지 증명함
* next값은 이전 스텍임, 이번 스텍이 끝나면 이전 스텍으로 이동함
*/
typedef struct EventPointNode
{

	VoidNode* NumNodeTable;
	VoidNode* StrNodeTable;
	VoidNode* ArrayNodeTable; // ArrayTable in EvenetPointNode 추가 시간 5월 10일 11시 55분

	int Event;
	size_t Point;
	void* data;

	struct EventPointNode* next;

} EventPointNode;

/*
* 스텍의 헤드임
*/
static EventPointNode* head = NULL;


/*
* stack seek라고 보면 됨
*/
EventPointNode* getEventPointNode()
{
	return head;
}

/*
* head의 이벤트 값을 가져옴
*/
int getEvent()
{
	return getEventPointNode()->Event;
};

/*
* head의 포인트 값을 가져옴
*/
size_t getPoint()
{
	return getEventPointNode()->Point;
};

/*
* stack push라고 보면 됨
*/
ErrorCode newEventPointNode(int Event, size_t Point)
{
	EventPointNode* Node = calloc(1, sizeof(EventPointNode));
	if (Node)
	{
		Node->Event = Event;
		Node->Point = Point;

		if (head) Node->next = head;
		head = Node;
	}
	else return ERROR_MEMORY_ALLOC_FAIL;
	return ERROR_NONE;
}

/*
* stack pop이라고 보면됨
* 다만 여기서는 seek의 기능이 없음
*/
ErrorCode popEventPointNode()
{
	if (head)
	{
		EventPointNode* Node = head;
		head = head->next;
		freeValNode(&Node->NumNodeTable);
		freeValNode(&Node->StrNodeTable);
		freeValNode(&Node->ArrayNodeTable);
		free(Node);
	}
	else return ERROR_NULL_POINTER;
	return ERROR_NONE;
}


#define StrSize 1024

/*
* 변수 생성
*/
ErrorCode newNumNode(int index, int d)
{
	EventPointNode* event = getEventPointNode();
	VoidNode** table = &event->NumNodeTable;
	ErrorCode error = ERROR_NONE;
	if (!*table)
	{
		error = newVoidNode(table);
		if (error != ERROR_NONE) return error;
	}
	if ( *table )
	{
		NumNode* node;
		error = newMalloc(&node, sizeof(NumNode));
		if (error != ERROR_NONE) return error;

		error = newValNode(table, index, node);
		if (error != ERROR_NONE) {
			free(node);
			return error;
		}

		node->data = d;
		//printf("선언\n%d: %d\n", index, node->data);

	}
	return ERROR_NONE;
}

/*
* 스트링 생성
*/
ErrorCode newStrNode(int index)
{
	EventPointNode* event = getEventPointNode();
	VoidNode** table = &event->StrNodeTable;
	ErrorCode error = ERROR_NONE;
	if (!*table)
	{
		error = newVoidNode(table);
		if (error != ERROR_NONE) return error;
	}
	if (*table)
	{
		StrNode* node;
		error = newMalloc(&node, sizeof(StrNode));
		if (error != ERROR_NONE) return error;

		error = newCalloc(&node->d, StrSize, sizeof(char));
		if (error != ERROR_NONE) return error;

		error = newValNode(table, index, node);
		if (error != ERROR_NONE) return error;

		node->size = StrSize;
		if (sprintf_s(node->d, node->size, "") == -1) return ERROR_ORRNO;


	}
	return ERROR_NONE;
}


/*
* nodeSearchFunction에 쓰는 콜백 함수
*/
typedef ErrorCode (*NodeFunction)(EventPointNode* event, int index, void* result);


/*
* EventPointNodeStack에서 Val를 찾아내는 함수
* 콜백 함수로 어떤 값을 찾을지와 어떤값을 수정하거나 가져올지 결정한다
*/
ErrorCode nodeSearchFunction(NodeFunction function, int index, void* result)
{
	EventPointNode* event = getEventPointNode();
	ErrorCode error = ERROR_NONE;
	while (event)
	{
		error = function(event, index, result);
		if (FileEvnet.ParentMemoryRead && error == ERROR_INVALID_VAL) event = event->next;
		else if (error != ERROR_NONE) return error;
		else if (error == ERROR_NONE) return error;
	}
	return ERROR_INVALID_VAL;
}

/*
* setNumNode의 콜백함수, val를 찾으면 값을 입력한다
*/
ErrorCode setNumNodeFunction(EventPointNode* event, int index, int* result)
{
	ErrorCode error = ERROR_NONE;
	VoidNode* table = event->NumNodeTable;

	NumNode* node;
	error = getValNode(table, index, &node); // 찾는다

	if (error == ERROR_NONE) node->data = *result; // 찾았으면 입력한다
	else if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		return ERROR_INVALID_VAL;
	}
	return error;
}

/*
* getNumNode의 콜백함수, val를 찾으면 값을 가져온다
*/
ErrorCode getNumNodeFunction(EventPointNode* event, int index, int* result)
{
	ErrorCode error = ERROR_NONE;
	VoidNode* table = event->NumNodeTable;
	
	NumNode* node;
	error = getValNode(table, index, &node); // 찾는다
	if (error == ERROR_NONE) *result = node->data; // 찾았으면 가져온다
	else if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		return ERROR_INVALID_VAL;
	}
	return error;
}

/*
* setStrNode의 콜백함수, val를 찾으면 Str의 마지막에 값을 붙인다
*/
ErrorCode setStrNodeFunction(EventPointNode* event, int index, char* result)
{
	ErrorCode error = ERROR_NONE;
	VoidNode* table = event->StrNodeTable;

	StrNode* node;
	error = getValNode(table, index, &node); // 찾는다
	if (error == ERROR_NONE) // 찾았으면 실행한다
	{

		(node)->len = strnlen_s((node)->d, (node)->size);
		if ((node)->size - 16 < (node)->len)
		{
			error = newRealloc(&node, (node)->size *= 2); // 길이가 길면 늘린다
			if (error != ERROR_NONE) return error;
		}

		strncat_s((node)->d, (node)->size, result, 1);
		//printf("%s\n", node->d);
	}
	return error;
}

/*
* getStrNode의 콜백함수, val를 찾으면 값을 가져온다
*/
ErrorCode getStrNodeFunction(EventPointNode* event, int index, char** result)
{
	ErrorCode error = ERROR_NONE;
	VoidNode* table = event->StrNodeTable;

	StrNode* node;
	error = getValNode(table, index, &node); // 찾는다
	if (error == ERROR_NONE) // 찾았으면 가져온다
	{
		*result = node->d;
	}
	else if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		return ERROR_INVALID_VAL;
	}
	return error;
}


/*
* 변수 값 수정
*/
ErrorCode setNumNode(int index, int d)
{
	return nodeSearchFunction(setNumNodeFunction, index, &d);
}

/*
* 변수 값 참조
*/
ErrorCode getNumNode(int index, int* d)
{
	return nodeSearchFunction(getNumNodeFunction, index, d);
}

/*
* 스트링 값 추가
*/
ErrorCode setStrNode(int index, char d)
{
	return nodeSearchFunction(setStrNodeFunction, index, &d);
}

/*
* 스트링 값 참조
*/
ErrorCode getStrNode(int index, char** block)
{
	return nodeSearchFunction(getStrNodeFunction, index, block);
}

#undef StrSize

/*
* 특수한 경우에 쓰는 data의 포인터
*/
void* getPointdata()
{
	return getEventPointNode()->data;
}

/*
* 특수한 경우에 쓰는 data의 포인터 주소
*/
void** getPointdataPointer()
{
	return &getEventPointNode()->data;
}

/*
* 반복문의 선언과 같을때 쓰는 함수
*/
ErrorCode PointdataMallocInt(size_t count)
{
	ErrorCode error;
	IntArray** data = (IntArray**)getPointdataPointer();

	error = newIntArray(data, count, count + 2);
	if (error != ERROR_NONE) return error;

	(*data)->count = count;
	(*data)->size = count+2;

	return ERROR_NONE;
}

/*
* 반복문의 내부에서 쓰는 함수
*/
ErrorCode getPointdataIntArray(IntArray** data)
{
	ErrorCode error;
	*data = getPointdata();
	if (!*data)
	{
		error = PointdataMallocInt(8);
		if (error != ERROR_NONE) return error;

		*data = getPointdata();
	}
	return ERROR_NONE;
}



// ArrayNode 부분이었던것, 이사왔음

ErrorCode getArrayNodeInTable(VoidNode** arrayTable, int arrayIndex, VoidNode** arrayPointer)
{
	ErrorCode error = ERROR_NONE;

	if (arrayIndex == 0) // 스코프 이리와잇!, 뭐 이정도는 애교로 받아주쇼
	{
		EventPointNode* epn = NULL;
		if (epn = getEventPointNode()) {
			if (!epn->NumNodeTable) {
				error = newVoidNode(&epn->NumNodeTable);
				if (error != ERROR_NONE) return error;
			}
			*arrayPointer = epn->NumNodeTable;
			return ERROR_NONE;
		}
		else return ERROR_NULL_POINTER;
	}

	if (!arrayTable) return ERROR_NULL_POINTER; // 테이블 변수가 없자나

	if (!*arrayTable) // 1차 테이블 할당
	{
		error = newVoidNode(arrayTable);
		if (error != ERROR_NONE) return ERROR_MEMORY_ALLOC_FAIL; // arrayNode 할당 실패

	}

	VoidNode* arrayNode = NULL; // 2차 ArrayNode 선언
	error = getValNode(*arrayTable, arrayIndex, &arrayNode); //2차 테이블 가져오기
	if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		error = newVoidNode(&arrayNode);
		if (error != ERROR_NONE) return error;

		error = newValNode(arrayTable, arrayIndex, arrayNode);
		if (error != ERROR_NONE) return error;

	}

	*arrayPointer = arrayNode;
	return ERROR_NONE;
}

ErrorCode setArrayNodeVal(VoidNode** arrayNode, int index, int val)
{
	ErrorCode error = ERROR_NONE;
	if (!arrayNode) return ERROR_NULL_POINTER;

	NumNode* block;
	error = getValNode(*arrayNode, index, &block);
	if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL)
	{
		error = newMalloc(&block, sizeof(NumNode));
		if (error != ERROR_NONE) return error;

		error = newValNode(arrayNode, index, block);
		if (error != ERROR_NONE) return error;

	}
	else if (error != ERROR_NONE) return error;

	block->data = val;

	return error;
}

ErrorCode getArrayNodeVal(VoidNode* arrayNode, int index, int* val)
{
	ErrorCode error = ERROR_NONE;
	if (!arrayNode) return ERROR_NULL_POINTER;

	NumNode* block;
	error = getValNode(arrayNode, index, &block);

	//printf("(error:%p)", arrayNode);
	if (error != ERROR_NONE) return error;

	*val = block->data;
	return error;
}

ErrorCode getArrayNodeValPointer(VoidNode* arrayNode, int index, int** val)
{
	ErrorCode error = ERROR_NONE;
	if (!arrayNode) return ERROR_NULL_POINTER;

	NumNode* block;
	error = getValNode(arrayNode, index, &block);
	if (error != ERROR_NONE) return error;

	*val = &block->data;
	return error;
}

ErrorCode arrayNodeCopy(VoidNode* a, VoidNode** b)
{
	ErrorCode error = ERROR_NONE;

	if (!a)
	{
		b = NULL;
		return ERROR_NONE;
	}

	if (*b)
	{
		return ERROR_POINTER_OVERLAP;
	}

	for (int index = 0; index < (1LL << 16); index++)
	{
		int val;
		error = getArrayNodeVal(a, index, &val);
		if (error != ERROR_NONE) continue;
		error = setArrayNodeVal(b, index, val);
	}
	error = ERROR_NONE;

	return error;
}

/*
* getArrayNode에서 쓰이는 콜백함수
* nodeSearchFunction의 인수로 넣어서 쓰인다
*/
ErrorCode getArrayNodeFunction(EventPointNode* event, int index, VoidNode** result)
{
	ErrorCode error = ERROR_NONE;

	if (!event->ArrayNodeTable) return ERROR_NULL_POINTER;

	error = getValNode(event->ArrayNodeTable, index, result);
	if (error != ERROR_NONE) return ERROR_INVALID_VAL;

	return error;
}

/*
* ArrayNode의 element를 수정하거나 생성합니다
* EventPointNode랑 링킹된 버전
*/
ErrorCode setArrayNode(int arrayIndex, int elementIndex, int val)
{
	ErrorCode error = ERROR_NONE;
	EventPointNode* event = getEventPointNode();

	VoidNode* arrayNode;
	error = getArrayNodeInTable(&event->ArrayNodeTable, arrayIndex, &arrayNode);
	if (error != ERROR_NONE) return error;
	//printf("(error:%p)", arrayNode);

	error = setArrayNodeVal(&arrayNode, elementIndex, val);
	return error;
}

/*
* ArrayNode의 element의 값을 가져옵니다
* EventPointNode랑 링킹된 버전
*/
ErrorCode getArrayNode(int arrayIndex, int elementIndex, int* val)
{
	ErrorCode error = ERROR_NONE;
	EventPointNode* event = getEventPointNode();

	VoidNode* arrayNode;
	error = getArrayNodeInTable(&event->ArrayNodeTable, arrayIndex, &arrayNode);
	if (error != ERROR_NONE) return error;
	//printf("(error:%p)", arrayNode);

	error = getArrayNodeVal(arrayNode, elementIndex, val);
	return error;
}

ErrorCode nodeSearchFunctionToArgIsDeep(NodeFunction function, int index, void* result, int deep)
{
	EventPointNode* event = getEventPointNode();

	while (deep--)
	{
		event = event->next;
		if (!event) return ERROR_INVALID_VAL;
	}
	
	return function(event, index, result);
}

/*
* ArrayNode를 복사해서 이동합니다.
* flag 1: 상위 스코프의 ArrayNode를 현재 스코프로 가져옵니다
* flag -1: ArrayNode를 현재 스코프에서 상위 스코프로 보냅니다
*/
ErrorCode arrayCopyInStack(int index, int flag)
{
	ErrorCode error = ERROR_NONE;
	VoidNode* currentArray = NULL;
	VoidNode* targetArray = NULL;

	EventPointNode* event = getEventPointNode();
	if (0 < flag)
	{
		error = nodeSearchFunctionToArgIsDeep(getArrayNodeFunction, index, (void*) & targetArray, flag);
		if (error != ERROR_NONE) return error;

		error = arrayNodeCopy(targetArray, &currentArray);
		if (error != ERROR_NONE) return error;

		error = newValNode(&event->ArrayNodeTable, index, currentArray);
		if (error == ERROR_POINTER_OVERLAP) {
			VoidNode** node = NULL;
			error = getValNodePointer(event->ArrayNodeTable, index, &node);
			if (error != ERROR_NONE) return error;
			error = freeValNode(node);
			if (error != ERROR_NONE) return error;
			error = newValNode(&event->ArrayNodeTable, index, currentArray);
		}

	}
	else if (flag < 0)
	{
		error = getArrayNodeInTable(&event->ArrayNodeTable, index, &currentArray);
		if (error != ERROR_NONE) return error;

		error = arrayNodeCopy(currentArray, &targetArray);
		if (error != ERROR_NONE) return error;
		
		//printf("%p %p\n", ((VoidNode*)(event->ArrayNodeTable->data[0]))->data[1], ((VoidNode*)(event->next->ArrayNodeTable->data[0]))->data[1]);

		int deep = -flag;
		while (deep--)
		{
			event = event->next;
			if (!event) return ERROR_INVALID_VAL;
		}

		error = newValNode(&event->ArrayNodeTable, index, targetArray);
		if (error == ERROR_POINTER_OVERLAP) {
			VoidNode** node = NULL;
			error = getValNodePointer(event->ArrayNodeTable, index, &node);
			error = freeValNode(node);
			error = newValNode(&event->ArrayNodeTable, index, targetArray);
		}

	}

	return error;
}

ErrorCode arrayMove(int currentArrayIndex, int currentArrayElementIndex, int targetArrayIndex, int targetArrayElementIndex, size_t count )
{
	ErrorCode error = ERROR_NONE;
	EventPointNode* event = getEventPointNode();

	VoidNode* bufferArray = NULL;
	{
		VoidNode* currentArray;
		error = getArrayNodeInTable(&event->ArrayNodeTable, currentArrayIndex, &currentArray);
		if (error != ERROR_NONE) return error;

		error = arrayNodeCopy(currentArray, &bufferArray);
		if (error != ERROR_NONE) return error;
	}

	VoidNode* targetArray;
	error = getArrayNodeInTable(&event->ArrayNodeTable, targetArrayIndex, &targetArray);
	if (error != ERROR_NONE) return error;

	for (size_t index = 0; index < count; index++)
	{
		int val;
		error = getArrayNodeVal(bufferArray, index + currentArrayElementIndex, &val);
		if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL) continue;
		else if (error != ERROR_NONE) return error;
		error = setArrayNodeVal(&targetArray, index + targetArrayElementIndex, val);
		if (error != ERROR_NONE) return error;
	}
	
	error = freeValNode(&bufferArray);
	return error;
}

ErrorCode arrayClear(int index)
{
	ErrorCode error = ERROR_NONE;
	if (index == 0) {
		freeValNode(&getEventPointNode()->NumNodeTable);
	}
	else {
		VoidNode* table = getEventPointNode()->ArrayNodeTable;
		if (!table) return ERROR_NULL_POINTER;
		VoidNode** node = NULL;
		error = getValNodePointer(table, index, &node);
		if (error != ERROR_NONE) return error;
		if (!node || !*node) return ERROR_NULL_POINTER;
		freeValNode(node);
	}
	return error;
}

ErrorCode arrayToString(int flag, int array, int index, int string)
{
	ErrorCode error = ERROR_NONE;

	if (flag & 0b1000) {
		error = getNumNode(array, &array);
		if (error != ERROR_NONE) return error;

		error = getNumNode(index, &index);
		if (error != ERROR_NONE) return error;

	}
	if (flag & 0b0100) {
		error = getNumNode(string, &string);
		if (error != ERROR_NONE) return error;

	}

	char direction = '=';
	switch (flag & 0b11) {
		case 0b01:
			direction = '>';
			break;
		case 0b10:
			direction = '<';
			break;
		case 0b11:
		{
			ErrorCode error = ERROR_NONE;
			EventPointNode* event = getEventPointNode();
			int i = 0;
			error = getArrayNode(array, index, &i);
			if ( (error == ERROR_INVALID_VAL) || (error == ERROR_NULL_POINTER) ) {
				direction = '<';
				break;
			}
			char* s = "";
			error = getStrNodeFunction(event, string, &s);
			if ((error == ERROR_INVALID_VAL) || (error == ERROR_NULL_POINTER)) {
				direction = '>';
				break;
			}
			if (error == ERROR_NONE) {
				return ERROR_UNEXPECTED;
				break;
			}
		}
			break;
	}

	int unit_size = ((flag >> 4) & 0b11) + 1;

	if (direction == '>') {

		EventPointNode* event = NULL;
		event = getEventPointNode();
		int string_len = 0;

		while (1) {
			int value = 0;
			error = getArrayNode(array, index + string_len, &value);

			for (int i = 0; i < unit_size; i++) {
				int val = (value >> (8 * i)) & 0xFF;
				if (val == 0) {
					value = 0;
					break;
				}
			}

			if (value == 0) {
				break;
			}

			string_len++;
		}
		string_len++;

		StrNode* stringNode = NULL;
		error = getValNode(event->StrNodeTable, string, &stringNode);
		if (error == ERROR_NULL_POINTER || error == ERROR_INVALID_VAL) {
			error = newMalloc(&stringNode, sizeof(StrNode));
			if (error != ERROR_NONE) {
				return error;
			}
			error = newCalloc(&stringNode->d, string_len, sizeof(char));
			if (error != ERROR_NONE) {
				return error;
			}
			stringNode->len = 0;
			stringNode->size = string_len;

			error = newValNode(&event->StrNodeTable, string, stringNode);
			if (error != ERROR_NONE) {
				return error;
			}
		}
		else if (error != ERROR_NONE) {
			return error;
		}
		else {
			stringNode->size = string_len;
			error = newRealloc(&stringNode->d, stringNode->size);
			if (error != ERROR_NONE) {
				return error;
			}
		}

		for (int array_index = 0; 1; array_index++ ) {
			int value = 0; error = getArrayNode(array, index + array_index, &value);
			for (int i = 0; i < unit_size; i++) {
				if (array_index * unit_size + i < string_len - 1) {
					stringNode->d[array_index * unit_size + i] = (value >> (8 * i)) & 0xFF;
					stringNode->len++;
				}
				else {
					value = 0; break;
				}

			}
			if (value == 0) break;
		}

		stringNode->d[string_len-1] = '\0';

	}
	else if (direction == '<') {
		char* string_data = NULL;
		error = getStrNode(string, &string_data);
		if (error != ERROR_NONE) return error;

		for (int arr = 0; *string_data; arr++) {
			int value = 0;
			for (int ind = 0; *string_data && ind < unit_size; ind++) {
				value |= (string_data++)[0] << (ind * 8);
			}
			if (value) {
				error = setArrayNode(array, index + arr, value);
			}
		}
	}
	else {
		return ERROR_UNEXPECTED;
	}
	return error;

} 