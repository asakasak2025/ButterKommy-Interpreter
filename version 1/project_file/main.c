
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


static const char ����[] = "����";
static const char �ڹ�[] = "�ڹ�";


// ��� �����ϴ� �ڽ�
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
				debug("�Ҵ� ����");
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
		debug("�Ҵ� ����");
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

	if (16777216 < box_count) debug("�ʿ��� �޸𸮰� �ʹ� Ů�ϴ�.");
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
		debug("�߸� �� �ε����� �������� �õ��߽��ϴ�.");
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
	size_t size = sizeof( ���� );
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == ����[i]) b++;
		if (str[i] == �ڹ�[i]) k++;
	}
	if (b == size - 1) return 1;
	if (k == size - 1) return 0;
	return -1;
}

// ������ �����ϴ� ���
// ���� ���⼭ ������ �׷��� ���̴� �� ������
typedef struct valNode
{
	int d;
	int name;
	struct valNode* next;
} valNode;

static valNode* valNode_head = { 0 }; // ������ �������� ������
static size_t valNodeCount = 0;

void newVal( int d, int name )
{
	valNode** node = &valNode_head;
	size_t* count = &valNodeCount;

	while (*node) node = &((*node)->next);
	*node = (valNode*)calloc(1, sizeof(valNode));
	if(!*node)debug("���� �޸� �Ҵ� ����");
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
		else debug("���� �޸� �Ҵ� ����");
	}
	if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
	if(*node) (*node)->d = d;
	else debug("���� �޸� �Ҵ� ����");


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
		else debug("���� �޸� �б� ����");
	}
	if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
	if (*node) (*node)->d = d;
	else debug("���� �޸� �Ҵ� ����");

}

int getVali(size_t index)
{
	if (valNodeCount <= index) return 0;
	valNode* node = valNode_head;
	for (size_t i = 0; i < index; i++)
	{
		if (node) node = node->next;
		else debug("���� �޸� �б� ����");
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
		else debug("���� �޸� �б� ����");
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
			debug("�Ҵ� ����");
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
		else debug("���� �޸� �б� ����");
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
	else debug("goto point ���� �Ҵ� �ȵ�");
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
	else debug("goto point �� �̸��� �������� ������");
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
	int d_[4]; // ���ƾƾƤ��ƾƾƾƤ��Ƥ������������Ƥ��ƾƤ��Ƥ��ƾƤ��ƾƤ�
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
	else debug("�̺�Ʈ ����Ʈ ���� ��� �Ҵ� ����, �����");
}

EventPointStack* getEventPointStack()
{
	EventPointStack** evnetPointStack = &EvnetPointStack_head;
	if (*evnetPointStack) while ((*evnetPointStack)->head)
	{
		evnetPointStack = &(*evnetPointStack)->head;
	}
	else debug("�̺�Ʈ�� ����");
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
	else debug("�̺�Ʈ�� ����");
	EventPointStack* get = *evnetPointStack;
	return get;
}

void endEventPointStack() // �ʿ������� �ְڳ� �ʹ�
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

void endFunction(int *oder, int* flag) // ���� ���� ���� �� �밡���� �����شٿ�
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
			setValn(++val->d_[1], val->d_[0]); // ���⿡�� ���µ� �迭�� �Ͻó�, ��¿���� ������
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


�����

0001 0001 ���� ���� ( 0000_0000 ) 0000_0000 0000_0000
0001 0010  �ؽ�Ʈ ���� ( 0000_0000 ) 0000_0000 ... 0000_0000 ( �ƽ�Ű )


�����

0010 �����ȣ ����1 ����2 ���� 3

���� 3 = ���� 1 + ���� 2

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

�̵���

0011 0001 ���� ��ġ
0011 0010 ���� �̵�
0011 0011 ���� �̵� ( ����, ��ȣ )
0011 0100 ���ǹ�
0011 0101 �ݺ��� ( x�� �ݺ� )
0011 0110 �ݺ��� ( x in range y )
0011 0111 �ݺ��� ( while x )
0011 1000 ����

0011 1001 �̵��� ���� ( end ������ ���� )
0011 1010 ���� ��ġ&���� ( �� �ѷ� �Լ� ����� )

0011 1011 ������ ( ������ ���������� ���� )

�Լ���

0100

0100 0001 print %d
0100 0010 print %s
0100 0011 print %s\n
0100 0100 scanf %d
0100 0101 scanf %c ( ������ ��Ʈ���� ���� �ϳ� �߰� )


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
			// �ƾ�
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
		case 8: // ���� ���� �밡���� ������
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
		else if( (buffer[0] == 1 && buffer[1] == 2) && 2 < bufferLen) // ��Ʈ�� ���� �̺�Ʈ
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
		debug("���� �� ����");
		return;
	}
	else
	{

		// ���� ���� ������� ������ ����
		size_t size = { 0 };
		{
			fseek(fp, 0, SEEK_END);
			size = ftell(fp);
			rewind(fp);
		}
		
		// ���� ���� ����� ����
		char* cat;
		{
			cat = (char*)malloc(size);
			if (!cat)
			{
				debug("���� �Ҵ� ������");
				return;
			}
		}

		// ���� �б�
		{
			
			for (size_t i = 0; i < size; i++)
			{
				int c = fgetc(fp);
				if (c == EOF) break;
				cat[i] = c;
			}

			fclose(fp);

			DebugPrintLn("���� �б⿡ �����Ͽ����ϴ�.\n");

		}

		//���� ���� �Ľ�
		{

			int flag = 0;
			for (size_t i = 0; i < size; i++)
			{
				{
					int r = bkcmp(cat + i);
					if (r == 0)
					{
						DebugPrint("�ڹ�");
						i += 3;
						flag = 1;
						setBox(0);
					}
					else if (r == 1)
					{
						DebugPrint("����");
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

	if (debugEvnet) // �Ľ� ������ Ȯ�� ����
	{

		DebugPrintLn("\n�Ľ��� �������Դϴ�\n");

		for (size_t i = 0; i < box_count; i++)
		{
			printf("%d", getBox(i));
			if (i % 4 == 3) printf(" ");
			if (i % 16 == 15) printf("\n");
		}

		DebugPrintLn("\n");

	}

	// ���� ����
	{
		engene(1);
		engene(0);
	}

	// ���� ����
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