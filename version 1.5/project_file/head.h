

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC_DEBUG

#ifdef MALLOC_DEBUG

static void* c_pointer_buffer;
#define c_alloc_print__(n, p, fa, ...) printf("%s %d: %s %p" fa "\n", __FILE__, __LINE__, #n, p, __VA_ARGS__)
#define c_alloc_print(n, p) c_alloc_print__(n, p, "")
#define c_alloc(f, ...) ( c_pointer_buffer = f(__VA_ARGS__),c_alloc_print(f, c_pointer_buffer), c_pointer_buffer ) 
#define malloc(s) c_alloc(malloc, s)
#define calloc(n, s) c_alloc(calloc, n, s)
#define realloc(p, s) (c_pointer_buffer = realloc(p, s), c_alloc_print__(realloc, p, " %p", c_pointer_buffer), c_pointer_buffer)
#define free(p) c_alloc_print(free, p); free(p);

#endif MALLOC_DEBUG

typedef enum
{
	ERROR_NONE,
	ERROR_MEMORY_ALLOC_FAIL,
	ERROR_INVALID_INDEX,
	ERROR_NULL_POINTER,
	ERROR_POINTER_OVERLAP,
	ERROR_ORRNO,
	ERROR_INVALID_VAL, // 해당 변수가 없는 경우
	ERROR_UNEXPECTED, // 예상치 못한 실패
	ERROR_OPERATION_FAILED // 연산 실패
} ErrorCode;

/*
* VoidNode 구조체입니다.
* 보통 이중 중첩한 2차원 테이블로 활용됩니다.
*/
typedef struct VoidNode
{
	void* data[256];
} VoidNode;

/*
* 포인트를 저장합니다
*/
typedef struct PointNode
{
	size_t point;
} PointNode;

typedef struct IntArray
{
	int* d;
	size_t count;
	size_t size;
} IntArray;



/*
* sub 파일의 선언부
*/

void debug(char* format);
void DebugPrint(char* format);
void DebugPrintln(char* format);


void _dp(char* format, int line);

/*
* 디버그 메시지
*/
#define dp(format) _dp(format, __LINE__)

/*
* 양식 준수형 malloc, 초기화도 됨
*/
ErrorCode newMalloc(void** block, size_t size);

/*
* 양식 준수형 calloc
*/
ErrorCode newCalloc(void** block, size_t count, size_t size);

/*
* 양식 준수형 realloc
*/
ErrorCode newRealloc(void** block, size_t size);


/*
* 에러 관련 함수
*/

/*
* 무슨 에러가 났는지 보여줍니다.
*/
void handleError(ErrorCode error);

/*
* index마다 할당된 errorCode를 반환합니다 GL 호환을 위해서 준비함
*/
ErrorCode getError(int index);

/*
* VoidNode 파일의 선언부
*/

/*
* CodeBox table의 시작
*/
ErrorCode CodeBoxBegin();

/*
* CodeBox table의 top
*/
size_t getCodeBoxTop();

/*
* CodeBox에 데이터 추가
* char 형태로 저장
*/
ErrorCode setCodeBox(char d);

/*
* CodeBox의 데이터 읽기
* char 형태로 읽음
*/
ErrorCode getCodeBox(size_t index, char* d);

/*
* CodeBoxTable의 End, 해당 테이블을 제거함
*/
ErrorCode CodeBoxTableEnd();

/*
* VoidNode를 생성합니다.
* 해당 VoidNode는 table 입니다.
* 객체에서 VoidNode talbe을 동적할당 하는 용도로 씁니다.
*/
ErrorCode newVoidNode(VoidNode** node);

/*
* VoidNode table에 block을 추가합니다
*/
ErrorCode newValNode(VoidNode** voidNode, int index, void* block);

/*
* VoidNode talbe의 block을 node에 할당합니다.
* 가져온 block은 원래 형태로 변환해서 사용해주세요.
*/
ErrorCode getValNode(VoidNode* voidNode, int index, void** node);

/*
* VoidNode talbe의 block의 주소를 node에 할당합니다.
*/
ErrorCode getValNodePointer(VoidNode* voidNode, int index, void*** node);

/*
* VoidNode talbe를 제거합니다.
* 보통 EvnetNode가 제거될때 호출됩니다.
*/
ErrorCode freeValNode(VoidNode** voidNode);


/*
* codeBox 파일의 선언부
*/




/*
* PointNode 파일의 선언부
*/

/*
* PointNode의 시작점
*/
ErrorCode PointNodeTableBegin();

/*
* PointNode를 할당합니다
* size_t 값을 받아서 저장합니다
*/
ErrorCode setPointNode(int index, size_t point);

/*
* PointNode의 값을 가져옵니다
* size_t 형태로 가져옵니다
*/
ErrorCode getPointNode(int index, size_t* point);

/*
* PointNodeTable를 끝냅니다.
*/
ErrorCode PointNodeTableEnd();



/*
* EventPointNode 파일의 선언부
*/

/*
* stack push라고 보면 됨
*/
ErrorCode newEventPointNode(int Event, size_t Point);

/*
* head의 포인트 값을 가져옴
*/
size_t getPoint();

/*
* head의 이벤트 값을 가져옴
*/
int getEvent();

/*
* stack pop이라고 보면됨
* 다만 여기서는 seek의 기능이 없음
*/
ErrorCode popEventPointNode();

/*
* 변수 생성
*/
ErrorCode newNumNode(int index, int d);

/*
* 변수 값 수정
*/
ErrorCode setNumNode(int index, int d);

/*
* 변수 값 참조
*/
ErrorCode getNumNode(int index, int* d);

/*
* 스트링 생성
*/
ErrorCode newStrNode(int index);

/*
* 스트링 값 추가
*/
ErrorCode setStrNode(int index, char d);

/*
* 스트링 값 참조
*/
ErrorCode getStrNode(int index, char** block);

/*
* 반복문의 선언과 같을때 쓰는 함수
*/
ErrorCode PointdataMallocInt(size_t count);



/*
* 반복문의 내부에서 쓰는 함수
*/
ErrorCode getPointdataIntArray(IntArray** data);


/*
* IntArray 파일의 선언부
*/

/*
* array<int>를 만드는 함수
*/
ErrorCode newIntArray(IntArray** data, size_t count, size_t size);

/*
* array<int>에서 값의 포인터를 꺼내는 함수
*/
ErrorCode getIntArrayDataPointer(IntArray* array, size_t index, int** d);

/*
* array<int>에서 값을 꺼내는 함수
*/
ErrorCode getIntArrayData(IntArray* array, size_t index, int* d);

/*
* array<int>에서 값을 저장하는 함수
*/
ErrorCode setIntArrayData(IntArray* array, size_t index, int d);

/*
* EventPointNode 파일의 선언부의 arrayNode의 부분
*/

/*
* ArrayNode의 값을 할당함
*/
ErrorCode setArrayNode(int arrayIndex, int elementIndex, int val);

/*
* ArrayNode의 값을 가져옴
*/
ErrorCode getArrayNode(int arrayIndex, int elementIndex, int* val);


/*
* ArrayNode을 상위 스텍에서 가져오거나 가져감
*/
ErrorCode arrayCopyInStack(int index, int flag);

/*
* ArrayNode를 cpy함
*/
ErrorCode arrayMove(int currentArrayIndex, int currentArrayElementIndex, int targetArrayIndex, int targetArrayElementIndex, size_t count);

/*
* ArrayNode를 제거함
*/
ErrorCode arrayClear(int index);

/*
* array <-> string 변환 연산을 수행함
*/
ErrorCode arrayToString(int flag, int array, int index, int string);

/*
* arrayEngine 파일의 선언부
*/

/*
* array 추가 구문 엔진 카운트 함수
*/
int arrayEngine_getCommandCount(int _index, int index_);

/*
* array 추가 구문 엔진 1
*/
ErrorCode arrayEngine_5(int buffer[], size_t* oder, int* flag);

/*
* array 추가 구문 엔진 2
*/
ErrorCode arrayEngine_6(int buffer[]);

/*
* array 추가 구문 엔진 3
*/
ErrorCode arrayEngine_7(int buffer[]);


