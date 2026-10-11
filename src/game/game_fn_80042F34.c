typedef int s32;
typedef void* OSMessage;

typedef struct OSThreadQueue {
    void* head;
    void* tail;
} OSThreadQueue;

typedef struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage* msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

extern OSMessageQueue lbl_803040B8;
extern s32 lbl_8064C7D0;
extern s32 fn_8020D318(OSMessageQueue*, OSMessage*, s32);

void fn_80042F34(void) {
    OSMessage message;

    if (lbl_8064C7D0 != 0) {
        fn_8020D318(&lbl_803040B8, &message, 1);
        lbl_8064C7D0 -= 1;
    }
}
