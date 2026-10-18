extern void* memset(void*, int, unsigned int);

typedef struct PadStatus {
    unsigned short button;
    signed char stickX;
    signed char stickY;
    signed char substickX;
    signed char substickY;
    unsigned char triggerL;
    unsigned char triggerR;
    unsigned char analogA;
    unsigned char analogB;
    signed char err;
} PadStatus;

typedef struct PadState {
    unsigned int held;
    unsigned int pressed;
    short stickX;
    short stickY;
    short substickX;
    short substickY;
    unsigned short triggerL;
    unsigned short triggerR;
    unsigned short analogA;
    unsigned short analogB;
    short prevStickX;
    short prevStickY;
    short prevSubstickX;
    short prevSubstickY;
} PadState;

typedef struct Entry {
    int field0;
    int field4;
    int field8;
    int fieldC;
    int state;
    int owner;
    int field18;
    unsigned int flags;
} Entry;

typedef struct InputData {
    PadStatus status[4];
    PadState pads[4];
    Entry entries[20];
} InputData;

extern InputData lbl_805B40C0;
extern int lbl_8064D048;
extern int lbl_8064D04C;
extern unsigned int lbl_8064D050;
extern int lbl_8064D060;
extern int lbl_8064D070;
extern int lbl_8064D074;
extern int lbl_8064D078;

extern int PADInit(void);
extern void VIWaitForRetrace(void);
extern void VIFlush(void);
extern int PADReset(unsigned int mask);
extern int PADRecalibrate(unsigned int mask);
extern unsigned int PADRead(PadStatus* status);
extern void fn_80145408(unsigned int ticks);

void fn_8014447C(int initialize)
{
    register InputData* data = &lbl_805B40C0;
    register PadStatus* status;
    register unsigned int scratch;
    register Entry* entries;

    if (initialize) {
        PADInit();
        VIWaitForRetrace();
        PADRecalibrate(0x80000000);
        VIWaitForRetrace();
        do {
            VIFlush();
            VIWaitForRetrace();
        } while (PADReset(0x80000000) != 1);
        VIFlush();
        VIWaitForRetrace();
        /* ASM: addi retains the zero-offset pooled address; C substitutes mr. */
        asm { addi scratch, data, 0 }
        PADRead((PadStatus*)scratch);
        /* ASM: addi preserves the separate controller-status address from the retail data pool; C folds it into the pool base. */
        asm { addi status, data, 0 }
        while (status->err < -1) {
            PADReset(0x80000000);
            fn_80145408(0xFB90);
            /* ASM: addi retains the zero-offset pooled address; C substitutes mr. */
            asm { addi scratch, data, 0 }
            PADRead((PadStatus*)scratch);
            lbl_8064D04C = status->err;
        }
        lbl_8064D04C = status->err;
        lbl_8064D060 = 0;
    }
    /* ASM: addi retains the zero-offset pooled address; C substitutes mr. */
    asm { addi scratch, data, 0 }
    lbl_8064D070 = 0;
    lbl_8064D050 = 0;
    memset((void*)scratch, 0, sizeof(data->status));
    memset(data->pads, 0, sizeof(data->pads));
    memset(data->entries, 0, sizeof(data->entries));
    /* ASM: addi and or retain a separate entry-array base. C folds the address into every store; or prevents that folding. */
    asm { addi entries, data, 0xB0
          or entries, entries, entries }
    /* Reset each slot in the fixed-size entry pool. */
    entries[0].state = -2;
    /* ASM: li reuses the address scratch register for the cleared counters. C assigns its zero constant to a different register. */
    asm { li scratch, 0 }
    entries[1].state = -2;
    entries[2].state = -2;
    entries[3].state = -2;
    entries[4].state = -2;
    entries[5].state = -2;
    entries[6].state = -2;
    entries[7].state = -2;
    entries[8].state = -2;
    entries[9].state = -2;
    entries[10].state = -2;
    entries[11].state = -2;
    entries[12].state = -2;
    entries[13].state = -2;
    entries[14].state = -2;
    entries[15].state = -2;
    entries[16].state = -2;
    entries[17].state = -2;
    entries[18].state = -2;
    entries[19].state = -2;
    lbl_8064D078 = (int)scratch;
    lbl_8064D074 = (int)scratch;
    lbl_8064D048 = (int)scratch;
}
