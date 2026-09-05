typedef struct DebugEntry {
    void* object;
    void* owner;
    volatile unsigned char active;
    unsigned char pad9;
    unsigned short timer;
} DebugEntry;

extern DebugEntry lbl_805B1268[6];
extern void fn_801409C0(unsigned char);

#pragma opt_propagation off
void fn_801409EC(void)
{
    DebugEntry* entries = lbl_805B1268;
    unsigned char i = 0;
    while (i < 6) {
        DebugEntry* entry = &entries[i];
        if ((int)entry->active == 1)
            fn_801409C0(i);
        i++;
    }
}
#pragma opt_propagation reset
