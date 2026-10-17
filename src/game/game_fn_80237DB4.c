typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;
typedef void (*DVDCallback)(s32 result, DVDFileInfo *file);

struct DVDCommandBlock {
    DVDCommandBlock *next;
    DVDCommandBlock *prev;
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void *addr;
    u32 currTransferSize;
    u32 transferredSize;
    void *id;
    void (*callback)(s32 result, DVDCommandBlock *block);
    void *userData;
};

struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    DVDCallback callback;
};

typedef void *OSMessage;
typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct OSMessageQueue {
    OSThreadQueue queueSend;
    OSThreadQueue queueReceive;
    OSMessage *msgArray;
    s32 msgCount;
    s32 firstIndex;
    s32 usedCount;
} OSMessageQueue;

typedef struct StreamBuffer {
    u8 data[0x4000];
    DVDFileInfo file;
    u8 padding[0x4FC];
    OSMessage messages[8];
    OSMessageQueue queue;
} StreamBuffer;

extern void fn_8020D1F0(OSMessageQueue *queue, OSMessage *messages, s32 count);
extern int fn_80213394(char *name, DVDFileInfo *file);
extern int fn_80213704(DVDFileInfo *file, void *addr, s32 length, s32 offset,
                       DVDCallback callback, s32 prio);
extern void fn_80237E7C(int result);

extern StreamBuffer lbl_80643C20;
extern s32 lbl_8064DC30;
extern s32 lbl_8064DC3C;
extern s32 lbl_8064DC48;
extern s32 lbl_8064DC50;
extern s32 lbl_8064DC54;
extern s32 lbl_8064DC74;

void fn_80237DB4(register char *input) {
    register char *name;
    register char *openName;
    register DVDCallback callback;
    register DVDCallback readCallback;
    register int result;
    register s32 offset;
    register s32 zero;
    register u32 length;
    register DVDFileInfo *file;

    /* ASM: or (mr) preserves the incoming name copy; C emits addi. */
    asm { or name, input, input }
    fn_8020D1F0(&lbl_80643C20.queue, lbl_80643C20.messages, 8);
    /* ASM: li rematerializes zero across DVDOpen; or (mr) preserves the
       argument copy that this compiler replaces with addi in C. */
    asm {
        li zero, 0
        or openName, name, name
    }
    lbl_8064DC3C = zero;
    fn_80213394(openName, &lbl_80643C20.file);
    file = &lbl_80643C20.file;
    zero = 0;
    /* ASM: lwz keeps the separate file base, which C folds into the offset. */
    asm { lwz length, 0x34(file) }
    lbl_8064DC50 = zero;
    lbl_8064DC54 = length;
    callback = (DVDCallback)fn_80237E7C;
    do {
        offset = lbl_8064DC50;
        /* ASM: or (mr) retains the callback register copy instead of addi. */
        asm { or readCallback, callback, callback }
        result = fn_80213704(&lbl_80643C20.file, lbl_80643C20.data, 0x2000,
                            offset, readCallback, 2);
    } while (result == 0);
    lbl_8064DC30 = 0x2000;
    lbl_8064DC50 += 0x2000;
    lbl_8064DC54 -= 0x2000;
    lbl_8064DC48 = 0;
    lbl_8064DC74 = 0;
}
