typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    s16 values[12];
    u32 flags;
} Entry;

extern void* lbl_8064D790;
extern void fn_801F5D28(void*);

#pragma use_lmw_stmw on

void fn_801F5C74(Entry* entry)
{
    u32 bit = 1;
    u16 i = 0;

    for (; i < 11; i++) {
        s16 value = entry->values[i];
        if (value != -1 && (entry->flags & (bit << i)) != 0) {
            fn_801F5D28((char*)lbl_8064D790 + value * 12);
        }
    }
}
