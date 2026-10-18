typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 state;
    u8 type;
    u8 arg2;
    u8 arg3;
    u8 padding04[76];
    u32 handle;
    u8 padding54[48];
} Entry;

extern Entry lbl_8060B430[];
extern u32 fn_801A9B94(u32, u32);
extern void sndStreamMixParameterEx(u32, u32, u32, u32, u32, u32);

void fn_801AECAC(void)
{
    int i;
    Entry* entry = lbl_8060B430;

    for (i = 0; i < 3; i++, entry++) {
        if (entry->state != 0) {
            u32 value = fn_801A9B94(entry->type, 2);
            sndStreamMixParameterEx(entry->handle, value, entry->arg2, entry->arg3, 0, 0);
        }
    }
}
