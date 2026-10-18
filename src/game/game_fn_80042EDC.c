typedef unsigned char u8;
typedef unsigned short u16;

typedef struct OSMessageQueue {
    void* sendHead;
    void* sendTail;
    void* receiveHead;
    void* receiveTail;
    void** messages;
    int messageCount;
    int firstIndex;
    int usedCount;
} OSMessageQueue;

typedef struct Message {
    u16 type;
    u16 arg;
    u8 immediate;
    u8 pad[3];
    OSMessageQueue* responseQueue;
} Message;

typedef struct Block {
    u8 pad00[0x2C];
    OSMessageQueue commandQueue;
    Message previousMessage;
    OSMessageQueue replyQueue;
    Message message;
} Block;

extern Block lbl_80304060;
extern int lbl_8064C7D0;
extern int OSSendMessage(OSMessageQueue*, void*, int);

void fn_80042EDC(void) {
    register Message* message = &lbl_80304060.message;

    lbl_80304060.message.type = 5;
    message->arg = 0;
    /* The reply queue occupies the 0x20 bytes immediately before this message. */
    message->responseQueue = (OSMessageQueue*)((u8*)message - sizeof(OSMessageQueue));
    ++lbl_8064C7D0;
    OSSendMessage(&lbl_80304060.commandQueue, message, 1);
}
