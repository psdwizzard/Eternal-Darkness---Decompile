typedef struct DebugEntry {
    void* object;
    void* owner;
    signed char active;
    unsigned char pad9;
    unsigned short timer;
} DebugEntry;

extern DebugEntry lbl_805B1268[6];
extern unsigned char lbl_8064D018;
extern void fn_801409C0(unsigned char index);

void fn_80140A58(void)
{
    unsigned char i = 0;

    while (i < 6) {
        DebugEntry* entry = &lbl_805B1268[i];
        if (entry->active == 1) {
            unsigned short* timer = &entry->timer;
            (*timer)--;
            if (*timer == 0) {
                fn_801409C0(i);
                lbl_8064D018--;
            }
        }
        i++;
    }
}
