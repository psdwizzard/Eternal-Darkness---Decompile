typedef int BOOL;
typedef unsigned long u32;
typedef BOOL (*OSResetFunction)(BOOL final);

typedef struct OSResetFunctionInfo {
    OSResetFunction func;
    u32 priority;
    struct OSResetFunctionInfo *next;
    struct OSResetFunctionInfo *prev;
} OSResetFunctionInfo;

typedef struct OSResetFunctionQueue {
    OSResetFunctionInfo *head;
    OSResetFunctionInfo *tail;
} OSResetFunctionQueue;

extern OSResetFunctionQueue ResetFunctionQueue_8064D960;

void OSRegisterResetFunction(OSResetFunctionInfo *info) {
    OSResetFunctionInfo *next;
    OSResetFunctionInfo *prev;

    for (next = ResetFunctionQueue_8064D960.head;
         next != 0 && next->priority <= info->priority;
         next = next->next) {
    }

    if (next == 0) {
        prev = ResetFunctionQueue_8064D960.tail;
        if (prev == 0) {
            ResetFunctionQueue_8064D960.head = info;
        } else {
            prev->next = info;
        }
        info->prev = prev;
        info->next = 0;
        ResetFunctionQueue_8064D960.tail = info;
    } else {
        info->next = next;
        prev = next->prev;
        next->prev = info;
        info->prev = prev;
        if (prev == 0) {
            ResetFunctionQueue_8064D960.head = info;
        } else {
            prev->next = info;
        }
    }
}
