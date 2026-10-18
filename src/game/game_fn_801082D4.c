typedef struct DataBlock {
    unsigned char header[0x18];
    unsigned char stack[0x1000];
    unsigned char thread[0x310];
    unsigned char queue0Storage[0x40];
    unsigned char queue0[0x20];
    unsigned char queue1Storage[0x40];
    unsigned char queue1[0x20];
} DataBlock;

extern DataBlock lbl_8032D648;
extern int lbl_8064CC70;
extern void* lbl_8064CC78;
extern int lbl_8064CC80;

extern void fn_801087D0(void);
extern void OSInitMessageQueue(void*, void*, int);
extern int OSReceiveMessage(void*, void**, int);
extern void OSInitMutex(void*);
extern void OSCreateThread(void*, void*, void*, void*, int, int, int);
extern void OSResumeThread(void*);

void fn_801082D4(register void* arg0)
{
    register unsigned long base = (unsigned long)&lbl_8032D648;
    register unsigned char* stack = ((DataBlock*)base)->stack;
    void* message;

    if (lbl_8064CC70 == 0) {
        OSInitMessageQueue((void*)(base + 0x13C8), (void*)(base + 0x1388), 0x10);
        OSInitMessageQueue((void*)(base + 0x1368), (void*)(base + 0x1328), 0x10);
        /* ASM: addi/bl retain the relocated zero-offset address calculation;
         * C canonicalizes it to an mr before the initialization call. */
        asm {
            addi r3, base, 0
            bl OSInitMutex
        }
        lbl_8064CC70 = 1;
    }

    while (OSReceiveMessage((void*)(base + 0x13C8), &message, 0) != 0) {
    }
    while (OSReceiveMessage((void*)(base + 0x1368), &message, 0) != 0) {
    }

    /* ASM: li/lis/addi/stw/mr preserve the retail interleaving of global
     * clears and thread-call argument construction, which C reassociates. */
    asm {
        li r0, 0
        lis r3, fn_801087D0@ha
        addi r6, r31, 0x18
        stw r0, lbl_8064CC80(r13)
        addi r4, r3, fn_801087D0@l
        mr r5, arg0
        stw r0, lbl_8064CC78(r13)
        addi r3, base, 0x1018
    }
    /* ASM: li/addi/bl keep the stack-top calculation separate from the
     * object address; the optimizer otherwise folds both equal pointers. */
    asm {
        li r7, 0x1000
        li r8, 8
        li r9, 1
        addi r6, r6, 0x1000
        bl OSCreateThread
    }
    OSResumeThread((void*)(base + 0x1018));
}
