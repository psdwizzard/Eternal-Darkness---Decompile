typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[4];
    s32 range;
    s32 period;
    unsigned char pad10[0x14];
    u16 counter;
    s16 adjustment;
    unsigned char pad28[1];
    unsigned char flags;
    unsigned char pad2A[6];
    s32 timer;
} Entry;

extern s32 lbl_8064D5A8;

extern Entry* fn_801FD6F4(u32);
extern u32 fn_8015C910(void);
extern s32 fn_800FBFB0(void);
extern void fn_801FDF74(u32, s32);
extern int fn_801FD9C0(u32);

int fn_801FDB10(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        if (entry->adjustment == 0x7FFF) {
            entry->counter -= 0x7FFF;
            entry->adjustment = 0;
            entry->timer = 0;
        }

        if (fn_8015C910() != 0 && (entry->flags & 1) != 0) {
            if (entry->counter != 0) {
                entry->counter++;
                if (entry->counter == 0xFFFF && entry->adjustment != 0) {
                    entry->counter -= entry->adjustment;
                    entry->adjustment = 0;
                    entry->timer = 0;
                }
            }
        } else {
            if (lbl_8064D5A8 % entry->period == 0) {
                s32 value = (fn_800FBFB0() << 2) + 1;
                fn_801FDF74(id, value % entry->range);
                entry->period = (fn_800FBFB0() & 7) + 1;
            }
            fn_801FD9C0(id);
        }
    }
    return 0;
}
