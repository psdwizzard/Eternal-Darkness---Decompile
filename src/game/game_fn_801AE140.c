typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 state;
    u8 value1;
    u8 value2;
    u8 value3;
    u8 padding04[76];
    void* source;
    u8 padding54[22];
    u8 mode;
    u8 padding6B[5];
    int active;
} Entry;

extern void fn_801AE368(Entry*);
extern void sndStreamMixParameterEx(void*, u32, u8, u8, u32, u32);

void fn_801AE140(Entry* entry, int stop)
{
    if (entry->state != 0) {
        if (stop != 0) {
            fn_801AE368(entry);
        } else if (entry->mode == 1 || entry->mode == 4) {
            if (entry->active == 0) {
                sndStreamMixParameterEx(entry->source, 0, entry->value2, entry->value3, 0, 0);
                entry->active = 1;
            }
        } else {
            fn_801AE368(entry);
        }
    }
}
