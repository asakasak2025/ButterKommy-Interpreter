
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void debug(char* format)
{
	puts(format);
	exit(-1);
}

static const _Bool debugEvnet = 0;


void DebugPrint(char* format)
{
	if (debugEvnet) printf(format);
}

void DebugPrintLn(char* format)
{
	if (debugEvnet) puts(format);
}


static const char 버터[] = "버터";
static const char 코미[] = "코미";


// 기계어를 저장하는 박스
typedef struct box
{
	char str[1024];
	struct box* next;
} Box;

static Box main_box = { 0 };
static size_t box_count = 0;

void newSizeBox()
{
	Box* s = &main_box;
	for (size_t i = 0; i < 1024; i++)
	{
		if ( NULL == (s = s->next))
		{
			s = malloc(sizeof(Box));
			if (s == NULL)
			{
				debug("할당 실패");
				return;
			}
		}
	}
}

Box* newBox()
{
	Box *box = (Box*)calloc(1, sizeof(Box));
	if (box == NULL)
	{
		debug("할당 실패");
		return NULL;
	}
	else
	{
		return box;
	}
}

void setBox(char get)
{
	size_t count = box_count;
	Box* box = &main_box;
	while (1023 < count)
	{
		count -= 1023;
		if (box->next == NULL) box->next = newBox();
		else box = box->next;
	}
	box->str[count] = get;
	box_count++;

	if (16777216 < box_count) debug("필요한 메모리가 너무 큽니다.");
}

char getBox(size_t index)
{
	if(index < box_count)
	{
		size_t count = index;
		Box* box = &main_box;
		while (1023 < count)
		{
			count -= 1023;
			if (box->next == NULL) while (box->next = newBox());
			else box = box->next;
		}
		return box->str[count];
	}
	else
	{
		debug("잘못 된 인덱스를 읽으려고 시도했습니다.");
		return '\0';
	}
}

void endBox()
{
	if (main_box.next)
	{
		Box* s = main_box.next;
		Box* n = { 0 };
		while (s)
		{
			n = s->next;
			free(s);
			s = n;
		}
	}
}

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

// 변수를 저장하는 노드
// 설마 여기서 변수는 그렇게 많이는 안 쓰겠지
typedef struct valNode
{
	int d;
	int name;
	struct valNode* next;
} valNode;

static valNode* valNode_head = { 0 }; // 변수가 없을수는 없지만
static size_t valNodeCount = 0;

void newVal( int d, int name )
{
	valNode** node = &valNode_head;
	size_t* count = &valNodeCount;

	while (*node) node = &((*node)->next);
	*node = (valNode*)calloc(1, sizeof(valNode));
	if(!*node)debug("변수 메모리 할당 오류");
	else
	{
		(*node)->d = d;
		(*node)->name = name;
	}
	*count += 1;
}

void setVali(int d, size_t index)
{
	valNode** node = &valNode_head;
	size_t count = index;

	for (size_t i = 0; i < count; i++)
	{
		if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
		if (*node) node = &((*node)->next);
		else debug("변수 메모리 할당 오류");
	}
	if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
	if(*node) (*node)->d = d;
	else debug("변수 메모리 할당 오류");


	if (valNodeCount <= index) valNodeCount = index + 1;
}

void setValn(int d, int name)
{
	valNode** node = &valNode_head;
	for (size_t i = 0; i < valNodeCount; i++)
	{
		if (*node)
		{
			if ((*node)->name == name) break;
			node = &(*node)->next;
		}
		else debug("변수 메모리 읽기 오류");
	}
	if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
	if (*node) (*node)->d = d;
	else debug("변수 메모리 할당 오류");

}

int getVali(size_t index)
{
	if (valNodeCount <= index) return 0;
	valNode* node = valNode_head;
	for (size_t i = 0; i < index; i++)
	{
		if (node) node = node->next;
		else debug("변수 메모리 읽기 오류");
	}
	if (node) return node->d; else return 0;
}

int getValn(int name)
{
	valNode* node = valNode_head;
	for (size_t i = 0; i < valNodeCount; i++)
	{
		if (node)
		{
			if (node->name == name) return node->d;
			node = node->next;
		}
		else debug("변수 메모리 읽기 오류");
	}
	return 0;
}

void endVal()
{
	if (valNode_head)
	{
		valNode* s = valNode_head;
		valNode* n = { 0 };
		while (s)
		{
			n = s->next;
			free(s);
			s = n;
		}
	}
}

Box* strVal_head = { 0 };
static size_t strValCount = 0;

void newStrValS1(char* format, int name)
{
	Box** node = &strVal_head;
	while (*node) node = &((*node)->next);
	*node = calloc(1, sizeof(Box));
	if (*node)
	{
		sprintf_s((*node)->str, 1023, "%s", format);
		(*node)->str[1023] = name;
		strValCount++;
	}
}

void newStrValC1(char format, int name)
{
	Box** node = &strVal_head;
	while (*node) node = &((*node)->next);
	*node = calloc(1, sizeof(Box));
	if (*node)
	{
		(*node)->str[0] = format;
		(*node)->str[1] = '\0';
		(*node)->str[1023] = name;
		strValCount++;
	}
}

void setStrVal(char format, int name)
{
	Box** node = &strVal_head;
	for (size_t i = 0; i < 1024; i++)
	{
		if (*node)
		{
			if ((*node)->str[1023] == name) break;
			else node = &(*node)->next;
		}
		else
		{
			debug("할당 실패");
		}
	}
	
	if (*node)
	{
		sprintf_s((*node)->str, 1023, "%s%c", (*node)->str, format);
	}

}

char* getStrVal(int name)
{
	Box* node = strVal_head;
	for (size_t i = 0; i < strValCount; i++)
	{
		if (node)
		{
			if (node->str[1023] == name) return node->str;
			node = node->next;
		}
		else debug("변수 메모리 읽기 오류");
	}
	return 0;
}

void endStrVal()
{
	Box* d = strVal_head;
	Box* b = { 0 };
	for (size_t i = 0; i < strValCount; i++)
	{
		if (d)
		{
			b = d;
			d = d->next;
			free(b);
		}
		else break;
	}
}

typedef struct PointValNode
{
	size_t d;
	int name;
	struct PointValNode* head;
} PointValNode;

PointValNode* PointValNode_head = NULL;

void setPointValNode(size_t d, int name)
{
	PointValNode** Node = &PointValNode_head;
	while (*Node) Node = &(*Node)->head;
	(*Node) = calloc(1, sizeof(PointValNode));
	if (*Node)
	{
		(*Node)->d = d;
		(*Node)->name = name;
	}
	else debug("goto point 동적 할당 안됨");
};

size_t getPointValNode(int name)
{
	PointValNode** Node = &PointValNode_head;
	while (*Node)
	{
		if ((*Node)->name == name) break;
		else Node = &(*Node)->head;
	}
	if (*Node)
	{
		return (*Node)->d;
	}
	else debug("goto point 그 이름을 가진것은 없수다");
	return 0;
}

void endPointValNode()
{
	PointValNode* d = PointValNode_head;
	PointValNode* b = NULL;
	while (d)
	{
		b = d;
		d = d->head;
		free(b);
	}
}

typedef struct EventPointStack
{
	int Event;
	size_t point;
	int d;
	int d_[4]; // 끄아아아ㅏ아아아아ㅏ아ㅏㅏㅏㅏㅏㅏ아ㅏ아아ㅏ아ㅏ아아ㅏ아아ㅏ
	struct EventPointStack* head;
} EventPointStack;

EventPointStack* EvnetPointStack_head = NULL;

void setEventPointStack(int Event, size_t point, int d)
{
	EventPointStack** evnetPointStack = &EvnetPointStack_head;
	while (*evnetPointStack) evnetPointStack = &(*evnetPointStack)->head;
	*evnetPointStack = calloc(1, sizeof(EventPointStack));
	if (*evnetPointStack)
	{
		(*evnetPointStack)->Event = Event;
		(*evnetPointStack)->point = point;
		(*evnetPointStack)->d = d;
	}
	else debug("이벤트 포인트 스텍 노드 할당 실패, 살려줘");
}

EventPointStack* getEventPointStack()
{
	EventPointStack** evnetPointStack = &EvnetPointStack_head;
	if (*evnetPointStack) while ((*evnetPointStack)->head)
	{
		evnetPointStack = &(*evnetPointStack)->head;
	}
	else debug("이벤트가 없어");
	EventPointStack* get = *evnetPointStack;
	*evnetPointStack = NULL;
	return get;
}

EventPointStack* seekEventPointStack()
{
	EventPointStack** evnetPointStack = &EvnetPointStack_head;
	if (*evnetPointStack) while ((*evnetPointStack)->head)
	{
		evnetPointStack = &(*evnetPointStack)->head;
	}
	else debug("이벤트가 없어");
	EventPointStack* get = *evnetPointStack;
	return get;
}

void endEventPointStack() // 필요한일이 있겠나 싶다
{
	EventPointStack* d = EvnetPointStack_head;
	EventPointStack* b = NULL;
	while (d)
	{
		b = d;
		d = d->head;
		free(b);
	}
}

void endFunction(int *oder, int* flag) // 누가 지금 깨진 내 대가리를 봉합해다오
{
	EventPointStack* val = seekEventPointStack();
	//printf("s");
	switch (val->Event)
	{
	case (3 << 4) + 4:
		if (val->d == 1) *flag = 0;
		free(getEventPointStack());
		break;
	case (3 << 4) + 5:
	{
		if (--val->d)
		{
			*oder = val->point;
		}
		else
		{
			free(getEventPointStack());
		}
	}
		break;
	case (3 << 4) + 6:
	{
		if (--val->d)
		{
			setValn(++val->d_[1], val->d_[0]); // 여기에만 쓰는데 배열을 하시네, 어쩔수가 없었어
			*oder = val->point;
		}
		else
		{
			free(getEventPointStack());
		}
	}
		break;
	case (3 << 4) + 7:
		if (getValn(val->d))
		{
			*oder = val->point;
		}
		else
		{
			free(getEventPointStack());
		}
		break;
	case (3 << 4) + 9:
	{
		EventPointStack* s = getEventPointStack();
		*oder = s->point;
		free(s);
	}
		break;
	}
}

void ifFunction(int buffer[], size_t* oder, int* flag)
{
	if (buffer[0] == 3) switch (buffer[1])
	{
	case 4:
		setEventPointStack((3 << 4) + 4, *oder, 0);
		break;
	case 5:
		setEventPointStack((3 << 4) + 4, *oder, 0);
		break;
	case 6:
		setEventPointStack((3 << 4) + 4, *oder, 0);
		break;
	case 7:
		setEventPointStack((3 << 4) + 4, *oder, 0);
		break;
	case 8:
		if (seekEventPointStack()->d == 1) *flag = 0;
		free(getEventPointStack());
		break;
	}
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

int getChar(size_t* index)
{

	int d = 0;
	for (size_t i = 0; i < 8; i++)
	{
		d += getBox(*index + i) << (7-i);
	}
	*index += 8;
	return d;
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
	}
	return -1;
}

#define intwoDefineFunction(i, d, a, b, c) case i: setValn(getValn(b) d getValn(c), a); break

void engeneFunction(int buffer[], size_t* oder, int* flag)
{
	switch (buffer[0])
	{
	case 1:
		switch (buffer[1])
		{
		case 1:
		{
			int format = (buffer[3] << 8) + buffer[4];
			newVal(format, buffer[2]);
			//printf("s");
		}
		break;
		case 2:
			// 아앗
			break;
		}
		break;
	case 2:
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
		break;
	case 3:
		switch (buffer[1])
		{
		case 2:
			*oder = getPointValNode(buffer[2]);
			break;
		case 3:
			if (buffer[2]) *oder = getPointValNode(buffer[3]);
			break;
		case 4:
			if ( !(0 < getValn(buffer[2]) ) ) *flag = 2;
			setEventPointStack((3 << 4) + 4, *oder, 1);
			break;
		case 5:
			setEventPointStack((3 << 4) + 5, *oder, buffer[2]);
			break;
		case 6:
			setEventPointStack((3 << 4) + 6, (*oder), buffer[3]);
			seekEventPointStack()->d_[0] = buffer[2];
			setValn(0, buffer[2]);
			break;
		case 7:
			if(getValn(buffer[2])) setEventPointStack((3 << 4) + 7, *oder, buffer[2]);
			else
			{
				setEventPointStack((3 << 4) + 4, *oder, 1);
				*flag = 2;
			}
			break;
		case 8: // 지금 본인 대가리가 깨진듯
			endFunction(oder, flag);
			break;
		case 9:
			setEventPointStack((3 << 4) + 9, *oder, 0);
			*oder = getPointValNode(buffer[2]);
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
			printf("%d", getValn(buffer[2]));
			break;
		case 2:
			printf("%s", getStrVal(buffer[2]));
			break;
		case 3:
			printf("%s\n", getStrVal(buffer[2]));
			break;
		case 4:
		{
			int get;
			fscanf_s(stdin, "%d", &get);
			setValn(get, buffer[2]);
		}
			break;
		case 5:
		{
			setStrVal(getc(stdin), buffer[2]);
		}
			break;
		}
		break;

	}
}

void engeneFunctionFirst(int buffer[], size_t* oder, size_t* firse_oder)
{
	switch (buffer[0])
	{
	case 3:
		switch (buffer[1])
		{
		case 1:
			setPointValNode(*oder, buffer[2]);
			break;
		case 10:
			setPointValNode(*oder, buffer[2]);
			break;
		case 11:
			*firse_oder = *oder;
			break;
		}
		break;
	}
}

void engene(int flag)
{
	size_t oder = 0;
	const size_t max = box_count;

	static size_t first_oder = 0;
	if (first_oder) oder = first_oder;

	int buffer[8] = { 0 };
	int bufferCount = -1;
	size_t bufferLen = 2;

	for (; oder < box_count - 7;)
	{
		const int get = getChar(&oder);
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
				newStrValC1(get, buffer[2]);
				bufferLen = 4;
			}
			else if (bufferLen == 4)
			{
				setStrVal(get, buffer[2]);
			}
			if (get == 0)
			{
				bufferCount = 0;
			}
			else bufferCount++;
		}
		else buffer[(bufferLen++) % 8] = get;

		if( bufferCount == 0 )
		{
			if (flag == 1) engeneFunctionFirst(buffer, &oder, &first_oder);
			if (flag == 0 ) engeneFunction(buffer, &oder, &flag);
			else if (flag == 2) ifFunction(buffer, &oder, &flag);
		}
		

		bufferCount -= 1;

	}
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

			DebugPrintLn("파일 읽기에 성공하였습니다.\n");

		}

		//읽은 정보 파싱
		{

			int flag = 0;
			for (size_t i = 0; i < size; i++)
			{
				{
					int r = bkcmp(cat + i);
					if (r == 0)
					{
						DebugPrint("코미");
						i += 3;
						flag = 1;
						setBox(0);
					}
					else if (r == 1)
					{
						DebugPrint("버터");
						i += 3;
						flag = 2;
						setBox(1);
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
				}

			}

		}

		free(cat);
		DebugPrint("\n");

	}

	if (debugEvnet) // 파싱 데이터 확인 영역
	{

		DebugPrintLn("\n파싱한 데이터입니다\n");

		for (size_t i = 0; i < box_count; i++)
		{
			printf("%d", getBox(i));
			if (i % 4 == 3) printf(" ");
			if (i % 16 == 15) printf("\n");
		}

		DebugPrintLn("\n");

	}

	// 실행 영역
	{
		engene(1);
		engene(0);
	}

	// 엔드 영역
	{
		DebugPrintLn("\n");
		endBox();
		endVal();
		endStrVal();
		endPointValNode();
		endEventPointStack();
	}

}

int main(int argc, char* argv[])
{
	if (argc == 2) main_(argv[1]);
	return 0;
}