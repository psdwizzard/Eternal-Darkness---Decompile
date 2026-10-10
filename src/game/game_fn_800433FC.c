typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct Message {
    u16 type;
    u16 arg;
    u8 immediate;
    u8 pad05[3];
    void* responseQueue;
} Message;

typedef struct DataBlock {
    u8 pad00[0x2C];
    u8 queue[0xF8 - 0x2C];
    u8 syncQueue[0x2428 - 0xF8];
    char path[0x80];
} DataBlock;

typedef struct Config {
    u8 pad00[0x10];
    void* buffer;
} Config;

extern char lbl_8023E9B8[];
extern DataBlock lbl_80304060;
extern Config lbl_8030241C;
extern volatile u32 lbl_8064C6AC[2];
extern u32 lbl_8064C6A4[2];
extern s32 lbl_8064CD78;
extern s32 lbl_8064CD74;

extern void fn_800433CC(void);
extern s32 fn_8020D318(void*, void*, s32);
extern s32 fn_8020D250(void*, void*, s32);
extern void fn_80043838(u16, u8);
extern void fn_80042CAC(u16, s32);
extern void fn_800B177C(s32, void (*)(void));
extern void fn_800B689C(s32, s32);
extern void fn_800B5D10(s32);
extern void fn_800B18F8(void);
extern void fn_8002487C(s32, s32);
extern s32 fn_8015AA14(void);
extern s32 fn_8015D458(void*, void*, s32);
extern void fn_8015DAB0(void*);
extern void fn_801380EC(void);
extern void fn_80138164(void);
extern s32 fn_8012070C(void);
extern s32 fn_8015E918(void*, s32, s32, s32, s32);
extern void fn_80042B54(void);
extern int fn_800F9D4C(char*, const char*, ...);

void fn_800433FC(void)
{
    volatile u32* buffers = lbl_8064C6AC;
    char* strings = lbl_8023E9B8;
    DataBlock* block = &lbl_80304060;
    Config* config = &lbl_8030241C;
    Message* received;
    Message* msg;
    void* reply;
    u32 file;
    u32 slot;

    for (;;) {
        fn_8020D318(block->queue, &received, 1);
        switch ((msg = received)->type) {
        case 1:
            msg->type = 2;
            reply = msg->responseQueue;
            msg->responseQueue = 0;
            fn_80043838(msg->arg, msg->immediate);
            break;
        case 3:
            msg->type = 4;
            reply = msg->responseQueue;
            msg->responseQueue = 0;
            fn_80042CAC(msg->arg, 1);
            break;
        case 5:
            fn_800B177C(1, fn_800433CC);
            fn_800B689C(1, 1);
            fn_800B5D10(0);
            fn_8020D318(block->syncQueue, 0, 1);
            fn_800B18F8();
            msg->type = 6;
            reply = msg->responseQueue;
            msg->responseQueue = 0;
            break;
        case 7:
            fn_8002487C(0x11, 0);
            reply = (void*)fn_8015D458(strings + 0xC8, config->buffer, fn_8015AA14());
            fn_8015DAB0(config->buffer);
            lbl_8064C6AC[0] = (u32)reply + (u32)config->buffer;
            buffers[1] = lbl_8064C6AC[0] + 0x27100;
            fn_801380EC();
            /* retail re-reads the second buffer pointer and discards it */
            buffers[1];
            fn_80138164();
            lbl_8064CD78 = fn_8015E918(strings + 0xD4, 0xE72D60, 0x330E0, fn_8012070C(), 0x330E0);
            lbl_8064CD74 = fn_8015E918(strings + 0xE4, 0xEA5E40, 0x15A1C0, fn_8012070C(), 0x15A1C0);
            fn_80042B54();
            msg->type = 8;
            reply = msg->responseQueue;
            msg->responseQueue = 0;
            break;
        case 9:
            file = msg->arg & 0xFFF;
            slot = (msg->arg >> 15) & 1;
            fn_800F9D4C(block->path, strings + 0xF4, file);
            fn_8015D458(block->path, (void*)lbl_8064C6AC[slot], 0x27100);
            fn_8015DAB0((void*)lbl_8064C6AC[slot]);
            lbl_8064C6A4[slot] = file;
            break;
        }
        if (reply != 0) {
            fn_8020D250(reply, msg, 1);
        }
        reply = 0;
    }
}
