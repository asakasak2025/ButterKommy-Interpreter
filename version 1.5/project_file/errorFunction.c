
#include "head.h"
#include <errno.h>

void handleError(ErrorCode error)
{
    switch (error)
    {
    case ERROR_MEMORY_ALLOC_FAIL:
        fprintf(stderr, "메모리 할당 실패\n");
        break;
    case ERROR_INVALID_INDEX:
        fprintf(stderr, "유효하지 않은 인덱스\n");
        break;
    case ERROR_NULL_POINTER:
        fprintf(stderr, "NULL 포인터 참조\n");
        break;
    case ERROR_POINTER_OVERLAP:
        fprintf(stderr, "같은 포인터에 덮어쓰기\n");
        break;
    case ERROR_ORRNO:
        fprintf(stderr, "ORRNO가 호출되었습니다. ORRNO: %d\n", errno);
        perror(errno);
    case ERROR_INVALID_VAL:
        fprintf(stderr, "해당 인덱스의 변수가 존재하지 않습니다\n");
        break;
    default:
        break;
    }
}

#define case_(index, log) case index: return log; break

/*
* index마다 할당된 errorCode를 반환합니다 GL 호환을 위해서 준비함
*/
ErrorCode getError(int index)
{
    switch (index)
    {
        case_(1, ERROR_MEMORY_ALLOC_FAIL);
        case_(2, ERROR_INVALID_INDEX);
        case_(3, ERROR_NULL_POINTER);
        case_(4, ERROR_POINTER_OVERLAP);
        case_(5, ERROR_ORRNO);
        case_(6, ERROR_INVALID_VAL);
    }
    return ERROR_NONE;
}

#undef case_