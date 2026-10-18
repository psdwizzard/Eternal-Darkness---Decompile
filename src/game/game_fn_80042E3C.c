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
    void* responseQueue;
} Message;

typedef struct Block {
    u8 pad[0x2C];
    OSMessageQueue commandQueue;
    Message message;
    OSMessageQueue replyQueue;
} Block;

extern Block lbl_80304060;
extern int lbl_8064C7D0;
extern int OSSendMessage(OSMessageQueue*, void*, int);

void fn_80042E3C(void) {
    Message* message = &lbl_80304060.message;

    lbl_80304060.message.type = 7;
    message->arg = 0;
    /* The reply queue immediately follows this message in the BSS block. */
    message->responseQueue = message + 1;
    ++lbl_8064C7D0;
    OSSendMessage(&lbl_80304060.commandQueue, message, 1);
}
