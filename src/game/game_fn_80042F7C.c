typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

typedef struct Message {
    u16 type;
    u16 mode;
    u8 immediate;
    u8 pad05[3];
    void* responseQueue;
} Message;

typedef struct DataBlock {
    u8 pad00[0x2C];
    u8 queue[0x20];
    u8 pad4C[0x38];
    Message message;
    u8 responseQueue[0x20];
} DataBlock;

extern DataBlock lbl_80304060;
extern s32 lbl_8064C7C8;
extern s32 lbl_8064C7CC;
extern s32 lbl_8064C7F4;
extern s32 fn_8020D250(void*, void*, s32);

void fn_80042F7C(s32 mode, s32 immediate)
{
    register Message* message;
    register s32 one;
    register void* responseQueue;
    register s32 zero;
    register DataBlock* block = &lbl_80304060;

    if (mode != lbl_8064C7CC) {
        message = &block->message;
        one = 1;
        responseQueue = block->responseQueue;
        zero = 0;

        message->immediate = immediate;
        message->type = one;
        message->mode = mode;
        lbl_8064C7CC = mode;
        message->responseQueue = responseQueue;
        lbl_8064C7C8 = one;
        lbl_8064C7F4 = zero;
        fn_8020D250(block->queue, message, one);
    }
}
