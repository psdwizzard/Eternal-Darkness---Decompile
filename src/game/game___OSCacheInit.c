typedef unsigned int u32;
typedef unsigned short OSError;
typedef struct OSContext OSContext;
typedef void (*OSErrorHandler)(OSError error, OSContext* context, ...);

extern u32 PPCMfhid0(void);
extern u32 PPCMfl2cr(void);
extern u32 PPCMfmsr(void);
extern void PPCMtmsr(u32 value);
extern void PPCMtl2cr(u32 value);
extern void ICEnable(void);
extern void DCEnable(void);
extern void L2GlobalInvalidate(void);
extern void DBPrintf(const char* format, ...);
extern OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler);
extern void DMAErrorHandler(OSError error, OSContext* context, ...);

/* Diagnostic strings shared by the SDK cache routines. */
extern char lbl_802FD178[];

void __OSCacheInit(void) {
    register char* messages;
    u32 savedMSR;
    register u32 cacheState;
    register OSErrorHandler handler;

    /* ASM: lis, addi keep string-pool setup after the register-save prologue;
     * C hoists lis ahead of the saves. */
    asm {
        lis r3, lbl_802FD178@ha
        addi messages, r3, lbl_802FD178@l
    }

    cacheState = PPCMfhid0();
    /* ASM: rlwinm keeps the HID0 mask separate from the unsigned comparison;
     * C combines them into a recording mask instruction. */
    asm { rlwinm cacheState, cacheState, 0, 16, 16 }
    if (cacheState == 0) {
        ICEnable();
        DBPrintf(messages + 0x1AC);
    }
    cacheState = PPCMfhid0();
    /* ASM: rlwinm preserves the separate data-cache mask and comparison. */
    asm { rlwinm cacheState, cacheState, 0, 17, 17 }
    if (cacheState == 0) {
        DCEnable();
        DBPrintf(messages + 0x1C8);
    }
    cacheState = PPCMfl2cr();
    /* ASM: clrrwi preserves the separate L2-enable mask and comparison. */
    asm { clrrwi cacheState, cacheState, 31 }
    if (cacheState == 0) {
        savedMSR = PPCMfmsr();
        /* ASM: sync orders cache and MSR changes; C has no hardware barrier. */
        asm { sync }
        PPCMtmsr(0x30);
        /* ASM: sync, sync serialize the MSR update and L2 disable;
         * C has no equivalent hardware barrier. */
        asm { sync; sync }
        PPCMtl2cr(PPCMfl2cr() & 0x7FFFFFFFu);
        /* ASM: sync completes the L2 disable before invalidation;
         * C has no equivalent hardware barrier. */
        asm { sync }
        L2GlobalInvalidate();
        PPCMtmsr(savedMSR);
        PPCMtl2cr((PPCMfl2cr() | 0x80000000u) & ~0x00200000u);
        DBPrintf(messages + 0x1E4);
    }
    /* ASM: lis, addi form the handler in the argument register using r3;
     * C selects r4 as the address scratch register. */
    asm {
        lis r3, DMAErrorHandler@ha
        addi handler, r3, DMAErrorHandler@l
    }
    OSSetErrorHandler(1, handler);
    DBPrintf(messages + 0x1FC);
}
