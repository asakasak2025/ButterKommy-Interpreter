
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


static const char 獄斗[] = "獄斗";
static const char 坪耕[] = "坪耕";


// 奄域嬢研 煽舌馬澗 酵什
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
				debug("拝雁 叔鳶");
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
		debug("拝雁 叔鳶");
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

	if (16777216 < box_count) debug("琶推廃 五乞軒亜 格巷 溺艦陥.");
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
		debug("設公 吉 昔畿什研 石生形壱 獣亀梅柔艦陥.");
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
	size_t size = sizeof( 獄斗 );
	for (size_t i = 0; i < size; i++)
	{
		if (str[i] == 獄斗[i]) b++;
		if (str[i] == 坪耕[i]) k++;
	}
	if (b == size - 1) return 1;
	if (k == size - 1) return 0;
	return -1;
}

// 痕呪研 煽舌馬澗 葛球
// 竺原 食奄辞 痕呪澗 益係惟 弦戚澗 照 床畏走
typedef struct valNode
{
	int d;
	int name;
	struct valNode* next;
} valNode;

static valNode* valNode_head = { 0 }; // 痕呪亜 蒸聖呪澗 蒸走幻
static size_t valNodeCount = 0;

void newVal( int d, int name )
{
	valNode** node = &valNode_head;
	size_t* count = &valNodeCount;

	while (*node) node = &((*node)->next);
	*node = (valNode*)calloc(1, sizeof(valNode));
	if(!*node)debug("痕呪 五乞軒 拝雁 神嫌");
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
		else debug("痕呪 五乞軒 拝雁 神嫌");
	}
	if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
	if(*node) (*node)->d = d;
	else debug("痕呪 五乞軒 拝雁 神嫌");


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
		else debug("痕呪 五乞軒 石奄 神嫌");
	}
	if (!*node) *node = (valNode*)calloc(1, sizeof(valNode));
	if (*node) (*node)->d = d;
	else debug("痕呪 五乞軒 拝雁 神嫌");

}

int getVali(size_t index)
{
	if (valNodeCount <= index) return 0;
	valNode* node = valNode_head;
	for (size_t i = 0; i < index; i++)
	{
		if (node) node = node->next;
		else debug("痕呪 五乞軒 石奄 神嫌");
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
		else debug("痕呪 五乞軒 石奄 神嫌");
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
			debug("拝雁 叔鳶");
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
		else debug("痕呪 五乞軒 石奄 神嫌");
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
	else debug("goto point 疑旋 拝雁 照喫");
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
	else debug("goto point 益 戚硯聖 亜遭依精 蒸呪陥");
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
	int d_[4]; // 塊焼焼焼た焼焼焼焼た焼たたたたたた焼た焼焼た焼た焼焼た焼焼た
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
	else debug("戚坤闘 匂昔闘 什努 葛球 拝雁 叔鳶, 詞形操");
}

EventPointStack* getEventPointStack()
{
	EventPointStack** evnetPointStack = &EvnetPointStack_head;
	if (*evnetPointStack) while ((*evnetPointStack)->head)
	{
		evnetPointStack = &(*evnetPointStack)->head;
	}
	else debug("戚坤闘亜 蒸嬢");
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
	else debug("戚坤闘亜 蒸嬢");
	EventPointStack* get = *evnetPointStack;
	return get;
}

void endEventPointStack() // 琶推廃析戚 赤畏蟹 粛陥
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

void endFunction(int *oder, int* flag) // 刊亜 走榎 凹遭 鎧 企亜軒研 裟杯背陥神
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
			setValn(++val->d_[1], val->d_[0]); // 食奄拭幻 床澗汽 壕伸聖 馬獣革, 嬢多呪亜 蒸醸嬢
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


識情採

0001 0001 収切 痕呪 ( 0000_0000 ) 0000_0000 0000_0000
0001 0010  努什闘 痕呪 ( 0000_0000 ) 0000_0000 ... 0000_0000 ( 焼什徹 )


尻至採

0010 尻至奄硲 痕呪1 痕呪2 痕呪 3

痕呪 3 = 痕呪 1 + 痕呪 2

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

戚疑採

0011 0001 壱燈 是帖
0011 0010 壱燈 戚疑
0011 0011 繕闇 戚疑 ( 繕闇, 腰硲 )
0011 0100 繕闇庚
0011 0101 鋼差庚 ( x腰 鋼差 )
0011 0110 鋼差庚 ( x in range y )
0011 0111 鋼差庚 ( while x )
0011 1000 殖球

0011 1001 戚疑板 軒渡 ( end 幻蟹檎 差瑛 )
0011 1010 壱燈 是帖&殖球 ( 戚 却稽 敗呪 幻球誌 )

0011 1011 獣拙繊 ( 蒸生檎 是拭辞採斗 獣拙 )

敗呪採

0100

0100 0001 print %d
0100 0010 print %s
0100 0011 print %s\n
0100 0100 scanf %d
0100 0101 scanf %c ( 奄糎税 什闘元拭 越切 馬蟹 蓄亜 )


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
			// 焼粧
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
		case 8: // 走榎 沙昔 企亜軒亜 凹遭牛
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
		else if( (buffer[0] == 1 && buffer[1] == 2) && 2 < bufferLen) // 什闘元 諮脊 戚坤闘
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
		debug("督析 公 石製");
		return;
	}
	else
	{

		// 石聖 舛左 煽舌社税 紫戚綜 著舛
		size_t size = { 0 };
		{
			fseek(fp, 0, SEEK_END);
			size = ftell(fp);
			rewind(fp);
		}
		
		// 石聖 舛左 煽舌社 持失
		char* cat;
		{
			cat = (char*)malloc(size);
			if (!cat)
			{
				debug("督析 拝雁 叔鳶敗");
				return;
			}
		}

		// 督析 石奄
		{
			
			for (size_t i = 0; i < size; i++)
			{
				int c = fgetc(fp);
				if (c == EOF) break;
				cat[i] = c;
			}

			fclose(fp);

			DebugPrintLn("督析 石奄拭 失因馬心柔艦陥.\n");

		}

		//石精 舛左 督縮
		{

			int flag = 0;
			for (size_t i = 0; i < size; i++)
			{
				{
					int r = bkcmp(cat + i);
					if (r == 0)
					{
						DebugPrint("坪耕");
						i += 3;
						flag = 1;
						setBox(0);
					}
					else if (r == 1)
					{
						DebugPrint("獄斗");
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

	if (debugEvnet) // 督縮 汽戚斗 溌昔 慎蝕
	{

		DebugPrintLn("\n督縮廃 汽戚斗脊艦陥\n");

		for (size_t i = 0; i < box_count; i++)
		{
			printf("%d", getBox(i));
			if (i % 4 == 3) printf(" ");
			if (i % 16 == 15) printf("\n");
		}

		DebugPrintLn("\n");

	}

	// 叔楳 慎蝕
	{
		engene(1);
		engene(0);
	}

	// 殖球 慎蝕
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