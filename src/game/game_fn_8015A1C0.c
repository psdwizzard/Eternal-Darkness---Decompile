typedef unsigned int u32;

typedef struct Record {
    char pad00[0x204C];
    int active;
    char pad2050[0x20];
    int value;
    int callback;
    char pad2078[0x28];
} Record;

extern Record lbl_805B70A0[];
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void VIWaitForRetrace(void);

Record* fn_8015A1C0(int direction, int callback, int value)
{
    Record* result = 0;
    int i;
    u32 interrupts;

    while (result == 0) {
        interrupts = OSDisableInterrupts();
        if (direction == 1) {
            for (i = 0; i < 2; i++) {
                if (lbl_805B70A0[i].active == 0) {
                    result = &lbl_805B70A0[i];
                    result->active = 1;
                    result->callback = callback;
                    result->value = value;
                    break;
                }
            }
        } else {
            for (i = 1; i >= 0; i--) {
                if (lbl_805B70A0[i].active == 0) {
                    result = &lbl_805B70A0[i];
                    result->active = 1;
                    result->callback = callback;
                    result->value = value;
                    break;
                }
            }
        }
        OSRestoreInterrupts(interrupts);
        if (result == 0) {
            VIWaitForRetrace();
        }
    }

    return result;
}
