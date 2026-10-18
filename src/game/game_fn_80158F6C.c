typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct RequestState {
    char pad00000[0x8140];
    s16 id;
    s8 flag142;
    s8 flag143;
    s8 active;
} RequestState;

typedef struct RequestGlobals {
    int current;
    char pad04[8];
    RequestState* volatile states[4];
} RequestGlobals;

extern volatile RequestGlobals lbl_805B6FE0;
extern char lbl_805B6FFC[];
extern int fn_80158E88(int);
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void OSSendMessage(void*, u32, int);

void fn_80158F6C(int id, int slot)
{
    u32 interrupts;
    int index;

    interrupts = OSDisableInterrupts();
    if (lbl_805B6FE0.states[slot]->active == 0) {
        index = fn_80158E88(id);
        if (index != -1) {
            u32 message;
            u32 request;

            message = slot ? 0x100000 : 0;
            lbl_805B6FE0.states[slot]->id = id;
            lbl_805B6FE0.states[slot]->flag142 = 0;
            lbl_805B6FE0.states[slot]->flag143 = 0;
            lbl_805B6FE0.states[slot]->active = 1;
            OSRestoreInterrupts(interrupts);
            request = id | 0x40000000 | (index << 12);
            OSSendMessage(lbl_805B6FFC,
                        (request | message), 1);
        } else {
            OSRestoreInterrupts(interrupts);
        }
    } else {
        OSRestoreInterrupts(interrupts);
    }
}
