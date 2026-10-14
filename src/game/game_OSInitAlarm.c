typedef unsigned char u8;
typedef void (*OSExceptionHandler)(u8 exception, void* context);

typedef struct OSAlarm OSAlarm;
typedef struct OSAlarmQueue {
    OSAlarm* head;
    OSAlarm* tail;
} OSAlarmQueue;

extern OSAlarmQueue AlarmQueue_8064D918;
extern OSExceptionHandler __OSGetExceptionHandler(u8 exception);
extern OSExceptionHandler __OSSetExceptionHandler(u8 exception, OSExceptionHandler handler);
extern void DecrementerExceptionHandler_8020AC88(u8 exception, void* context);

void OSInitAlarm(void)
{
    if (__OSGetExceptionHandler(8) != DecrementerExceptionHandler_8020AC88) {
        AlarmQueue_8064D918.head = AlarmQueue_8064D918.tail = 0;
        __OSSetExceptionHandler(8, DecrementerExceptionHandler_8020AC88);
    }
}
