typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Entry {
    unsigned char pad00[0x22];
    unsigned short state;
    unsigned char pad24[2];
    s16 step;
    unsigned char pad28[8];
    u32 time;
    unsigned char pad34[0x38];
    int (*callback)(u32);
} Entry;

extern Entry* fn_801FD6F4(u32);
extern u32 lbl_8064D7C8;

int fn_801FE110(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    int result = 0;
    if (entry != 0) {
        if (entry->time == 0 && entry->step != 0) {
            entry->step = 0;
            entry->time = 0x10000;
        }
        if (entry != 0) {
            s32 count;
            int i;

            if ((entry->time >> 16) > entry->step) {
                count = (entry->time >> 16) - entry->step;
                for (i = 0; i < count; i++) {
                    result = result || entry->callback(id);
                    entry->step++;
                }
            }
            entry->time += lbl_8064D7C8;
        }
    }
    return result;
}
