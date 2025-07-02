

#include "head.h"

int arrayEngine_getCommandCount(int _index, int index_)
{
	switch (_index)
	{
	case 5:
		switch (index_)
		{
		case 1:
			return 6;
			break;
		case 2:
			return 6;
			break;
		case 3:
			return 6; // 가변형임
			break;
		}
		break;
	case 6:

		return 12;
		break;
	case 7:
		switch (index_)
		{
		case 1:
			return 10;
			break;
		case 2:
			//return 7;
			return 3;
			break;
		case 3:
			return 7;
			break;
		case 4:
			return 2;
			break;
		}
		break;
	}
	return -1;
}

/*
* 단순하쥬?
*/
static inline int getValue(int buffer[], int i) {
	return (buffer[(i << 1) + 2 ] << 8) | (buffer[(i << 1) + 3]);
}

ErrorCode arrayEngine_5(int buffer[], size_t* oder, int* flag)
{
	ErrorCode error = ERROR_NONE;

	switch (buffer[1])
	{
	case 1:
	{
		int arr, index, val; (arr = getValue(buffer, 0), index = getValue(buffer, 1), val = getValue(buffer, 2));
		error = setArrayNode(arr, index, val);
	}
		break;
	case 2:
	{
		int arr, index, val; (arr = getValue(buffer, 0), index = getValue(buffer, 1), val = getValue(buffer, 2));
		error = getNumNode(index, &index);
		error = setArrayNode(arr, index, val);
	}
		break;
	case 3:
	{
		int arr, index, count; (arr = getValue(buffer, 0), index = getValue(buffer, 1), count = getValue(buffer, 2));
		unsigned get[2] = { 0, 0 };
		int j = 0;
		for (int i = 0, j = 0; *oder < getCodeBoxTop() && i < count; (j == 1) ? (j = 0, i++) : j++) {
			error = getCodeBox(oder[0]++, &get[j]);
			if (error != ERROR_NONE) return error;
			else if (j == 1) {
				int value = ((get[0] << 8) | get[1]);
				error = setArrayNode(arr, index + i, value);
				//{ int g = 0; error = getArrayNode(arr, index + i, &g); printf("\n%d: %d\n", __LINE__, g); }
				if (error != ERROR_NONE) return error;
			}
		}
	}
		break;
	}

	return error;
}

#define intwoDefineFunctionFunction(i, d, a, b, c) case i: c = a d b; break
#define intwoDefineFunction(i, d) intwoDefineFunctionFunction(i, d, value[1], value[2], value[0])
#define getValue(buffer, i) getValue(buffer, i-2)

ErrorCode arrayEngine_6(int buffer[])
{
	ErrorCode error = ERROR_NONE;

	int arrarg[3][2] = { {getValue(buffer, 2), getValue(buffer, 3)} , {getValue(buffer, 4), getValue(buffer, 5)}, {getValue(buffer, 6), getValue(buffer, 7)} };
	int value[3] = { 0 };

	int arrp[3][2] = { { 0 } };
	for (int i = 0; i < 3; i++) {
		arrp[i][0] = arrarg[i][0];
		error = getNumNode(arrarg[i][1], &arrp[i][1]);
	}

	//for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) printf("(value[%d][%d]: %d)", i, j, arrp[i][j]); puts("");

	for (int i = 1; i < 3; i++) {
		error = getArrayNode(arrp[i][0], arrp[i][1], &value[i]);
		//handleError(error);
		//error = getNumNode(arrp[i][1], &value[i]);
	}

	switch (buffer[1])
	{
		intwoDefineFunction(1, +);
		intwoDefineFunction(2, -);
		intwoDefineFunction(3, *);
		intwoDefineFunction(4, /);
		intwoDefineFunction(5, %);
		intwoDefineFunction(6, ==);
		intwoDefineFunction(7, !=);
		intwoDefineFunction(8, <);
		intwoDefineFunction(9, <=);
		intwoDefineFunction(10, >);
		intwoDefineFunction(11, >=);
		intwoDefineFunction(12, ||);
		intwoDefineFunction(13, &&);
		intwoDefineFunction(14, <<);
		intwoDefineFunction(15, >>);
	}

	error = setArrayNode(arrp[0][0], arrp[0][1], value[0]);
	return error;
}

#undef getValue
#undef intwoDefineFunction
#undef intwoDefineFunctionFunction

ErrorCode arrayEngine_7(int buffer[])
{
	ErrorCode error = ERROR_NONE;

	switch (buffer[1])
	{
	case 1:
	{
		int value[2][2] = { 0 };
		int count = 0;
		{
			int* buf_p = buffer + 2;
			for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
				value[i][j] = (buf_p[0] << 8) | buf_p[1];
				buf_p += 2;
			}
			count = (buf_p[0] << 8) | buf_p[1];
		}
		error = arrayMove(value[0][0], value[0][1], value[1][0], value[1][1], count);
	}
		break;
	case 2:
	{
		char flag = buffer[2];
		int arr = (buffer[3] << 8) | buffer[4];
		error = arrayCopyInStack(arr, flag);
	}
		break;
	case 3:
	{
		int flag = buffer[2];
		int arr = (buffer[3] << 8) | buffer[4];
		int index = (buffer[5] << 8) | buffer[6];
		int str = (buffer[7] << 8) | buffer[8];
		error = arrayToString(flag, arr, index, str);
	}
		break;
	case 4:
	{
		error = arrayClear((buffer[2] << 8) | buffer[3]);
	}
		break;
	}

	return error;
}

