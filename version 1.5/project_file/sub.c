
#include "head.h"

extern const _Bool debugEvnet;

void debug(char* format)
{
	puts(format);
	exit(-1);
}

void DebugPrint(char* format)
{
	if (debugEvnet) printf(format);
}

void DebugPrintln(char* format)
{
	if (debugEvnet) puts(format);
}

ErrorCode newMalloc(void** block, size_t size)
{
	*block = calloc(1, size);
	if (!*block) return ERROR_MEMORY_ALLOC_FAIL;
	return ERROR_NONE;
}

ErrorCode newCalloc(void** block, size_t count, size_t size)
{
	*block = calloc(count, size);
	if (!*block) return ERROR_MEMORY_ALLOC_FAIL;
	return ERROR_NONE;
}

ErrorCode newRealloc(void** block, size_t size)
{
	void* Block = realloc(*block, size);
	if (!Block) return ERROR_MEMORY_ALLOC_FAIL;
	*block = Block;
	return ERROR_NONE;
}

void _dp(char* format, int line)
{
	printf("line: %d, %s\n", line, format);
}