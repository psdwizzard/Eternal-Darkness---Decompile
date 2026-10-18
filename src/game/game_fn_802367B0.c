typedef unsigned char u8;
typedef int s32;

typedef struct StreamRequest {
    s32 command;
    char name[0x50];
    void *buffer;
    void *replyQueue;
} StreamRequest;

typedef struct StreamWork {
    u8 data[0x443C];
    StreamRequest request;
    u8 reserved[0xE0];
    u8 replyQueue[0x20];
    u8 replyQueueStorage[0x20];
    u8 requestQueue[0x20];
    u8 reservedQueues[0x2310];
    void *messages[8];
    u8 initQueue[0x20];
} StreamWork;

extern StreamWork lbl_80643C20;
extern s32 lbl_8064C64C;
extern s32 lbl_8064DC34;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC40;
extern s32 lbl_8064DC44;
extern s32 lbl_8064DC70;

extern char *fn_800FD40C(char *, const char *);
extern void OSInitMessageQueue(void *, void *, s32);
extern s32 OSSendMessage(void *, void *, s32);
extern void fn_8022F700(void *, s32);
extern void fn_8022F75C(void);
extern void *fn_8022F780(s32);
extern void fn_8022F854(void *, s32);

void fn_802367B0(const char *name, void *arena)
{
    register StreamWork *work;
    void *buffer;
    const char *sourceName = name;
    void *scratch;
    register StreamRequest *request;

    work = &lbl_80643C20;
    lbl_8064DC44 = 0;
    lbl_8064DC40 = lbl_8064C64C;
    if (lbl_8064DC38 == 0 && lbl_8064DC34 == 0) {
        OSInitMessageQueue(work->initQueue, work->messages, 8);
        fn_8022F700(arena, 0x3C000);
        fn_8022F75C();
        buffer = fn_8022F780(0x10000);
        scratch = fn_8022F780(0x4C00);
        fn_8022F854(scratch, 0x4C00);
        work->request.command = 3;
        request = &work->request;
        fn_800FD40C(request->name, sourceName);
        /* ASM: addi reconstructs the request address after the string call;
         * C otherwise retains the address across the call. */
        asm { addi request, work, 0x443C }
        request->replyQueue = work->replyQueue;
        request->buffer = buffer;
        OSSendMessage(work->requestQueue, request, 1);
        {
            register s32 zero;
            register s32 status;
            /* ASM: li/li materialize the status and reset together at the end.
             * Literal C assignments make MWCC retain zero in an extra saved
             * register across the allocation calls and reorder these stores. */
            asm {
                li status, 2
                li zero, 0
            }
            lbl_8064DC34 = status;
            lbl_8064DC70 = zero;
        }
    } else {
        /* Preserve the second read of the asynchronous stream state. */
        (void)lbl_8064DC38;
    }
}
