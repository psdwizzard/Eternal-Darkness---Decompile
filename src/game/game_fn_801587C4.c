typedef unsigned int u32;

typedef struct Entry {
    char pad00[8];
    int active;
    char pad0C[12];
} Entry;

extern Entry lbl_805B6E00[];
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void VIWaitForRetrace(void);

Entry* fn_801587C4(void)
{
    u32 interrupts;
    int index = 0;
    Entry* entry;

    interrupts = OSDisableInterrupts();
    for (;;) {
        entry = &lbl_805B6E00[index];
        if (entry->active == 0) {
            entry->active = 1;
            break;
        }
        index++;
        if ((u32)index >= 16) {
            index = 0;
            OSRestoreInterrupts(interrupts);
            VIWaitForRetrace();
            interrupts = OSDisableInterrupts();
        }
    }
    OSRestoreInterrupts(interrupts);
    return entry;
}
