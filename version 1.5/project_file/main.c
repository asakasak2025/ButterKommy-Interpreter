

#include "head.h"

const _Bool debugEvnet = 0;

#define BK_FILE_UTF8 1
#define BK_ADD_TEXT_MODE 1
// #define CONSOLE_UTF8 1 // visual studio 의 window 환경 전용

#ifndef BK_FILE_UTF8

static const char 버터[] = "버터";
static const char 코미[] = "코미";

#else

static const char 버터[] = u8"버터";
static const char 코미[] = u8"코미";

#endif




int bkcmp(char str[])
{
	size_t b = 0;
	size_t k = 0;
	size_t size = sizeof( 버터 );
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == 버터[i]) b++;
		if (str[i] == 코미[i]) k++;
	}
	if (b == size - 1) return 1;
	if (k == size - 1) return 0;
	return -1;
}


ErrorCode endFunction(int *oder, int* flag) // 누가 지금 깨진 내 대가리를 봉합해다오
{
	ErrorCode error = ERROR_NONE;

	IntArray* array;
	error = getPointdataIntArray(&array);
	if (error == ERROR_NULL_POINTER && getEvent() == (3 << 4) + 11);
	else if (error != ERROR_NONE) return error;

	//printf("s");
	switch (getEvent())
	{
	case (3 << 4) + 4:
	{
		int d;
		error = getIntArrayData(array, 0, &d);
		if (d == 1) *flag = 0;
		popEventPointNode();
	}
		break;
	case (3 << 4) + 5:
	{
		int* d;
		error = getIntArrayDataPointer(array, 0, &d);
		if (--(*d) ) *oder = getPoint();
		else popEventPointNode();
	}
		break;
	case (3 << 4) + 6:
	{
		int* d;
		error = getIntArrayDataPointer(array, 0, &d);
		if (--(*d))
		{
			*oder = getPoint();

			int* name;
			int* number;
			error = getIntArrayDataPointer(array, 1, &name);
			error = getIntArrayDataPointer(array, 2, &number);

			(*number)++;

			error = setNumNode(*name, *number);

		}
		else popEventPointNode();
	}
		break;
	case (3 << 4) + 7:
	{
		int d;
		int cmp;
		error = getIntArrayData(array, 0, &d);
		error = getNumNode(d, &cmp);
		if (cmp)
		{
			*oder = getPoint();
		}
		else popEventPointNode();
	}
		break;
	case (3 << 4) + 9:
	{
		*oder = getPoint();
		popEventPointNode();
	}
		break;
	case (3 << 4) + 11:
		popEventPointNode();
	}
	return ERROR_NONE;
}

ErrorCode ifFunction(int buffer[], size_t* oder, int* flag)
{
	ErrorCode error;
	if (buffer[0] == 3) switch (buffer[1])
	{
	case 4:
	case 5:
	case 6:
	case 7:
	{
		error = newEventPointNode((3 << 4) + 11, *oder);
	}
		break;
	case 8:
	{
		IntArray* array;
		error = getPointdataIntArray(&array);

		int d;
		error = getIntArrayData(array, 0, &d);
		if (d == 1)
		{
			error = popEventPointNode();
			*flag = 0;
		}
	}
		break;
	}
	return ERROR_NONE;
}

/*


선언부

0001 0001 숫자 변수 ( 0000_0000 ) 0000_0000 0000_0000
0001 0010  텍스트 변수 ( 0000_0000 ) 0000_0000 ... 0000_0000 ( 아스키 )


연산부

0010 연산기호 변수1 변수2 변수 3

변수 3 = 변수 1 + 변수 2

+ 0001
-  0010
* 0011
/ 0100
% 0101
== 0110
!= 0111
< 1000
<= 1001
> 1010
>= 1011
|| 1100
&& 1101
<< 1110
>> 1111

이동부

0011 0001 고투 위치
0011 0010 고투 이동
0011 0011 조건 이동 ( 조건, 번호 )
0011 0100 조건문
0011 0101 반복문 ( x번 반복 )
0011 0110 반복문 ( x in range y )
0011 0111 반복문 ( while x )
0011 1000 엔드

0011 1001 이동후 리턴 ( end 만나면 복귀 )
0011 1010 고투 위치&엔드 ( 이 둘로 함수 만드삼 )

0011 1011 시작점 ( 없으면 위에서부터 시작 )

함수부

0100

0100 0001 print %d
0100 0010 print %s
0100 0011 print %s\n
0100 0100 scanf %d
0100 0101 scanf %c ( 기존의 스트링에 글자 하나 추가 )


*/

//int getChar(size_t* index)
//{
//
//	int d = 0;
//	for (size_t i = 0; i < 8; i++)
//	{
//		d += getBox(*index + i) << (7-i);
//	}
//	*index += 8;
//	return d;
//}

ErrorCode getChar(char buffer[])
{
	int d = 0;
	for (size_t i = 0; i < 8; i++)
	{
		d += buffer[i] << (7 - i);
	}
	return setCodeBox(d);
}

int getCommandCount(int _get, int get_)
{
	switch (_get)
	{
	case 1:
		switch (get_)
		{
		case 1:
			return 3;
			break;
		case 2:
			return 8;
			break;
		}
		break;
	case 2:
		if (0 < get_ && get_ < 14) return 3;
		break;
	case 3:
		switch (get_)
		{
		case 1:
			return 1;
			break;
		case 2:
			return 1;
			break;
		case 3:
			return 2;
			break;
		case 4:
			return 1;
			break;
		case 5:
			return 1;
			break;
		case 6:
			return 2;
			break;
		case 7:
			return 1;
			break;
		case 8:
			return 0;
			break;
		case 9:
			return 1;
			break;
		case 10:
			return 1;
			break;
		case 11:
			return 0;
			break;
		}
		break;
	case 4:
		switch (get_)
		{
		case 1:
			return 1;
			break;
		case 2:
			return 1;
			break;
		case 3:
			return 1;
			break;
		case 4:
			return 1;
			break;
		case 5:
			return 1;
			break;
		}
		break;
	default:

		return arrayEngine_getCommandCount(_get, get_);

		break;
	}
	return -1;
}

#define intwoDefineFunction(i, d) case i: c = a d b; break

ErrorCode engeneFunction(int buffer[], size_t* oder, int* flag)
{
	ErrorCode error = ERROR_NONE;

	switch (buffer[0])
	{
	case 1:
		switch (buffer[1])
		{
		case 1:
		{
			int format = (buffer[3] << 8) + buffer[4];
			error = newNumNode(buffer[2], format);
			if (error == ERROR_POINTER_OVERLAP) {
				error = setNumNode(buffer[2], format);
			}
			//puts("변수 생성 완료");
			//printf("s");
		}
		break;
		case 2:
			// 아앗
			break;
		}
		break;
	case 2:
	{
		int a, b, c = 0;
		error = getNumNode(buffer[3], &a);
		//if (error != ERROR_NONE)
		//{
		//	dp("\n에러 등장"), handleError(error);
		//}

		error = getNumNode(buffer[4], &b);
		//if (error != ERROR_NONE)
		//{
		//	dp("\n에러 등장"), handleError(error);
		//}

		

		switch (buffer[1])
		{
			intwoDefineFunction(1, +, buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(2, -, buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(3, *, buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(4, / , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(5, %, buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(6, == , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(7, != , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(8, < , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(9, <= , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(10, > , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(11, >= , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(12, || , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(13, &&, buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(14, << , buffer[2], buffer[3], buffer[4]);
			intwoDefineFunction(15, >> , buffer[2], buffer[3], buffer[4]);
		}

		//printf("\n %d: %d, %d: %d, %d: %d \n", buffer[3], a, buffer[4], b, buffer[2], c);

		error = setNumNode(buffer[2], c);
	}
		break;
	case 3:
		switch (buffer[1])
		{
		case 2:
		{
			size_t d;
			error = getPointNode(buffer[2], &d);
			*oder = d;
		}
			break;
		case 3:
		{
			if (buffer[2])
			{
				size_t d;
				error = getPointNode(buffer[3], &d);
				*oder = d;
			}
		}
			break;
		case 4:
		{
			int d;
			error = getNumNode(buffer[2], &d);
			if (!(0 < d)) *flag = 2;

			error = newEventPointNode((3 << 4) + 4, *oder);

			error = PointdataMallocInt(1);

			IntArray* array;
			error = getPointdataIntArray(&array);

			error = setIntArrayData(array, 0, 1);
		}
			break;
		case 5:
		{
			error = newEventPointNode((3 << 4) + 5, *oder);

			error = PointdataMallocInt(1);

			IntArray* array;
			error = getPointdataIntArray(&array);

			error = setIntArrayData(array, 0, buffer[2]);
		}
			break;
		case 6:
		{
			error = newEventPointNode((3 << 4) + 6, *oder);

			error = PointdataMallocInt(3);

			IntArray* array;
			error = getPointdataIntArray(&array);

			error = setIntArrayData(array, 0, buffer[3]);

			error = setIntArrayData(array, 1, buffer[2]);

			error = setIntArrayData(array, 2, 0);

			error = newNumNode(buffer[2], 0);
		}
			break;
		case 7:
		{
			int d;
			error = getNumNode(buffer[2], &d);

			if (d)
			{
				error = newEventPointNode((3 << 4) + 7, *oder);

				error = PointdataMallocInt(1);

				IntArray* array;
				error = getPointdataIntArray(&array);

				error = setIntArrayData(array, 0, buffer[2]);
			}
			else
			{
				error = newEventPointNode((3 << 4) + 4, *oder);

				error = PointdataMallocInt(1);

				IntArray* array;
				error = getPointdataIntArray(&array);

				error = setIntArrayData(array, 0, 1);

				*flag = 2;
			}
		}
			break;
		case 8: // 지금 본인 대가리가 깨진듯 -> 23시간 후의 나다 임마, 너 보다 내가 더 아픈것 같다
			endFunction(oder, flag);
			break;
		case 9:
		{
			error = newEventPointNode((3 << 4) + 9, *oder);

			size_t d;
			error = getPointNode(buffer[2], &d);

			*oder = d;
		}
			break;
		case 10:
			endFunction(oder, flag);
			break;
		}
		break;
	case 4:
		switch (buffer[1])
		{
		case 1:
		{
			int d = 0;
			error = getNumNode(buffer[2], &d);
			//handleError(error);
			printf("%d", d);
		}
			break;
		case 2:
		{
			char* d = NULL;
			error = getStrNode(buffer[2], &d);
			printf("%s", d);
		}
			break;
		case 3:
		{
			char* d;
			error = getStrNode(buffer[2], &d);
			
			if (error == ERROR_NONE ) puts(d);

			if (error != ERROR_NONE) handleError(error);
		}
			break;
		case 4:
		{
			int get;
			fscanf_s(stdin, "%d", &get);
			setNumNode(buffer[2], get);
		}
			break;
		case 5:
		{
			char get = getc(stdin);
			setStrNode(buffer[2], get);
		}
			break;
		}
		break;
	case 5:
		error = arrayEngine_5(buffer, oder, flag);
		return error;
		break;
	case 6:
		error = arrayEngine_6(buffer);
		return error;
		break;
	case 7:
		error = arrayEngine_7(buffer);
		return error;
		break;
	}
	return ERROR_NONE;
}

void engeneFunctionFirst(int buffer[], size_t* oder, size_t* firse_oder)
{
	ErrorCode error;
	switch (buffer[0])
	{
	case 3:
		switch (buffer[1])
		{
		case 1:
		{
			size_t d = *oder;
			error = setPointNode(buffer[2], d);
		}
			break;
		case 10:
		{
			size_t d = *oder;
			error = setPointNode(buffer[2], d);
		}
			break;
		case 11:
			*firse_oder = *oder;
			break;
		}
		break;
	}
}

#define buffer_size 32

ErrorCode engene(int flag)
{
	size_t oder = 0;
	const size_t max = getCodeBoxTop();

	static size_t first_oder = 0;
	if (first_oder) oder = first_oder;

	int buffer[buffer_size] = { 0 };
	int bufferCount = -1;
	size_t bufferLen = 2;
	ErrorCode error;

	for (; oder < getCodeBoxTop();)
	{
		unsigned char get;
		error = getCodeBox(oder++, &get);
		if (error != ERROR_NONE)
		{
			puts("읽기 오류가 발생하였습니다.");
			handleError(error);
			return error;
		}

		const int _get = get >> 4;
		const int get_ = get & 0xF;

		//printf("\noder: %llu, get: %d %d, count: %d, len: %llu flag: %d; buffer: %d %d %d %d \n", oder, (get & 0xF0) >> 4, get & 0x0F, bufferCount, bufferLen, flag, buffer[0], buffer[1], buffer[2], buffer[3] );
		
		if (bufferCount < 0)
		{
			buffer[0] = _get;
			buffer[1] = get_;
			bufferLen = 2;
			bufferCount = getCommandCount(_get, get_);
		}
		else if( (buffer[0] == 1 && buffer[1] == 2) && 2 < bufferLen) // 스트링 삽입 이벤트
		{
			if (flag == 1)
			{

			}
			else if (bufferLen == 3)
			{

				error = newStrNode(buffer[2]);
				handleError(error);
				error = setStrNode(buffer[2], get);
				handleError(error);
				
				bufferLen = 4;
			}
			else if (bufferLen == 4)
			{
				error = setStrNode(buffer[2], get);
				handleError(error);
			}
			if (get == 0)
			{
				bufferCount = 0;
			}
			else bufferCount++;
		}
		else buffer[(bufferLen++) % buffer_size] = get;

		if( bufferCount == 0 )
		{
			if (flag == 1) engeneFunctionFirst(buffer, &oder, &first_oder);
			if (flag == 0 ) engeneFunction(buffer, &oder, &flag);
			else if (flag == 2) ifFunction(buffer, &oder, &flag);
		}

		bufferCount -= 1;

	}

	return ERROR_NONE;
}

#undef buffer_size

#ifdef BK_ADD_TEXT_MODE

typedef struct {
	char*** d;
	size_t count;
} Parser;

#define BUFFER_SIZE 1024
#define fileScanf(a, b) fscanf_s(fp, " %[^:]: %[^\n] ", a, BUFFER_SIZE, b, BUFFER_SIZE)
#define isSpace(x) ( ((x) == 32) || 9 <= (x) && (x) <= 13 )

// 비비 따잇을 실현화 하는 함수
Parser* main_plus(char* format)
{
	FILE* fp = fopen(format, "r");
	if (!fp) {
		debug("파일을 읽지 못했소");
		return NULL;
	}
	else {

		
		if (fgetc(fp) == 0xEF) if (fgetc(fp) == 0xBB) if (fgetc(fp) == 0xBF) goto GOTO_BOM;
		
		fseek(fp, 0, SEEK_SET);

	GOTO_BOM:;
		
		char*** three = NULL;
		size_t count = 0;
		size_t size = 2;

		struct {
			char x[BUFFER_SIZE];
			char y[BUFFER_SIZE];
		} b = { {0}, {0} };
		
		three = malloc(size * sizeof(void*));
		if (!three) goto GOTO_ERROR_FREE_THREE;

		while (1) {

			if (count == size) {

				size *= 2;
				char*** routput = realloc(three, size * sizeof(void*));
				if (!routput) goto GOTO_WHILE_ERROR;
				three = routput;

			}

			int error = fileScanf(b.x, b.y);
			if (error != 2) break;

			char** pair = malloc(2 * sizeof(void*));
			if (!pair) goto GOTO_ERROR_FREE_ARRAY_ELEMENT;

			size_t x_size = strnlen(b.x, BUFFER_SIZE) - 1;
			size_t y_size = strnlen(b.y, BUFFER_SIZE) - 1;

			for (; x_size != (size_t)(-1) && isSpace(b.x[x_size]); b.x[x_size--] = '\0');
			for (; y_size != (size_t)(-1) && isSpace(b.y[y_size]); b.y[y_size--] = '\0');

			x_size++;
			y_size++;

			char* x = malloc(x_size + 1);
			if (!x) goto GOTO_WHILE_ERROR_X;
			char* y = malloc(y_size + 1);
			if (!y) goto GOTO_WHILE_ERROR_Y;

			memcpy(x, b.x, x_size);
			memcpy(y, b.y, y_size);

			x[x_size] = '\0';
			y[y_size] = '\0';

			pair[0] = x;
			pair[1] = y;

			three[count++] = pair;

			continue; // 아래는 에러 구문

		GOTO_WHILE_ERROR_Y:
			free(x);
		GOTO_WHILE_ERROR_X:
			free(pair);

		GOTO_WHILE_ERROR:
			goto GOTO_ERROR_FREE_ARRAY_ELEMENT;
		}

		Parser* parser = malloc(sizeof(Parser));
		if (!parser) goto GOTO_ERROR_FREE_ARRAY_ELEMENT;

		fclose(fp);

		parser->d = three;
		parser->count = count;

		return parser;

	GOTO_ERROR_FREE_ARRAY_ELEMENT:
		for (int i = 0; i < count; i++) {
			free(three[i][0]);
			free(three[i][1]);
			free(three[i]);
		}

	GOTO_ERROR_FREE_THREE:
		free(three);
		fclose(fp);

		return NULL;
	}
	return NULL;
}

int add_parser(char* cat, size_t size)
{

	Parser* parser = main_plus("code_list.txt");
	if (!parser) {
		DebugPrintln("code_list.txt 파일에 대해서 오류가 발생했습니다.");
		return -1;
	}
	else {

		char*** key = parser->d;
		size_t count = parser->count;
		free(parser);
		char* parser = "NONE";
		ErrorCode error = 0;

		char buffer[8] = { 0, };
		size_t buffer_top = 0;

		if(debugEvnet) for (int i = 0; i < count; i++) {
			printf("(%s) : (%s)\n", key[i][0], key[i][1]);
		}

		for (size_t i = 0; i < size; i++) {

			for (size_t j = 0; j < count; j++) if (cat[i] == key[j][0][0]) for (size_t k = 0; !key[j][0][k] || cat[i+k] == key[j][0][k]; k++) if (!key[j][0][k]) for (size_t l = 0; 1; l++) {
				if (!key[j][1][l]) {
					i += k-1;
					goto GOTO_BREAK;
				}
				if (key[j][1][l] == '0') buffer[buffer_top++] = 0;
				if (key[j][1][l] == '1') buffer[buffer_top++] = 1;
				if (7 < buffer_top) {
					error = getChar(buffer);
					buffer_top = 0;
				}
			}

		GOTO_BREAK:;

		}

		for (size_t i = 0; i < count; i++) {
			free(key[i][0]);
			free(key[i][1]);
		}
		free(key);

	}
	return 0;

}

#endif

int default_parser(char* cat, size_t size)
{

	int flag = 0;
	char buffer[8] = { 0, };
	size_t buffer_top = 0;

	for (size_t i = 0; i < size; i++)
	{

		int r = bkcmp(cat + i);
		if (r == 0)
		{
			DebugPrint(코미);
			i += 3;
			flag = 1;
			buffer[buffer_top++] = 0;
		}
		else if (r == 1)
		{
			DebugPrint(버터);
			i += 3;
			flag = 2;
			buffer[buffer_top++] = 1;
		}
		else if (r == -1)
		{
			if (cat[i] == ' ' && flag != 3)
			{
				DebugPrint(" ");
				flag = 3;
				//setBox(3);
			}

			if (cat[i] == '\n' /* && flag != 3*/)
			{
				DebugPrint("\n");
				flag = 3;
				//setBox(3);
			}
		}

		if (7 < buffer_top)
		{
			ErrorCode error = getChar(buffer);
			buffer_top = 0;

			if (error != ERROR_NONE) handleError(error);
		}

	}

	return 0;

}

void main_(char* format)
{
	FILE* fp = fopen(format, "r");
	if (!fp)
	{
		debug("파일 못 읽음");
		return;
	}
	else
	{

		// 읽을 정보 저장소의 사이즈 측정
		size_t size = { 0 };
		{
			fseek(fp, 0, SEEK_END);
			size = ftell(fp);
			rewind(fp);
		}
		
		// 읽을 정보 저장소 생성
		char* cat;
		{
			cat = (char*)malloc(size);
			if (!cat)
			{
				debug("파일 할당 실패함");
				return;
			}
		}

		// 파일 읽기
		{
			
			for (size_t i = 0; i < size; i++)
			{
				int c = fgetc(fp);
				if (c == EOF) break;
				cat[i] = c;
			}

			fclose(fp);

			DebugPrintln("파일 읽기에 성공하였습니다.\n");

		}

		// 저장소 시작
		{
			ErrorCode error;
			error = CodeBoxBegin();
			if (error != ERROR_NONE) handleError(error);

			error = PointNodeTableBegin();
			if (error != ERROR_NONE) handleError(error);

		}

		//읽은 정보 파싱
		{
#ifdef BK_ADD_TEXT_MODE
			if (add_parser(cat, size) != -1); else
#endif
				default_parser(cat, size);
		}

		free(cat);
		DebugPrint("\n");

	}

	if (debugEvnet) // 파싱 데이터 확인 영역
	{

		DebugPrintln("\n파싱한 데이터입니다\n");

		printf("%d\n", (int)getCodeBoxTop());

		ErrorCode error;
		for (size_t i = 0; i < getCodeBoxTop(); i++)
		{
			
			int d[2] = { 0, };
			int get;
			error = getCodeBox(i, &get);

			d[0] = get & 0xF0;
			d[0] = d[0] >> 4;
			d[1] = get & 0x0F;

			printf("%x %x ", d[0], d[1]);
			if (i % 4 == 3) printf(" ");
			if (i % 16 == 15) printf("\n");
		}

		DebugPrintln("\n");

	}

	// 맨 처음 이벤트
	{
		newEventPointNode(0, 0);
	}

	// 실행 영역
	{
		engene(1);
		engene(0);
	}

	// 엔드 영역
	{
		DebugPrintln("\n");
		
		PointNodeTableEnd();
		popEventPointNode();
		CodeBoxTableEnd();
		/*endBox();
		endVal();
		endStrVal();
		endPointValNode();
		endEventPointStack();*/
	}

}

#ifdef CONSOLE_UTF8

#include <Windows.h>

#endif

int main(int argc, char* argv[])
{
#ifdef CONSOLE_UTF8
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
#endif
	if (argc == 2) main_(argv[1]);
	return 0;
}