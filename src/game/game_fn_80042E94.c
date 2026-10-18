typedef void* OSMessage;

typedef struct OSThreadQueue {
    void* head;
    void* tail;
} OSThreadQueue;

typedef struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage* msgArray;
    int msgCount;
    int firstIndex;
    int usedCount;
} OSMessageQueue;

extern OSMessageQueue lbl_803040B8;
extern int lbl_8064C7D0;
extern int OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, int flags);

void fn_80042E94(void) {
    OSMessage message;

    if (lbl_8064C7D0 != 0) {
        OSReceiveMessage(&lbl_803040B8, &message, 1);
        lbl_8064C7D0 -= 1;
    }
}
