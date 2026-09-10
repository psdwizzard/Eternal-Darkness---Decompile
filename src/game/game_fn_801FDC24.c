typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[0x1C];
    s16 remaining;
    u16 state;
    u16 counter;
    s16 adjustment;
    unsigned char pad28[8];
    s32 timer;
} Entry;

extern Entry* fn_801FD6F4(u32);
extern void fn_801FDDB0(u32);
extern void fn_801FEA44(u32);
extern int fn_801FE05C(u32);
extern void fn_801FDE24(u32);
extern int fn_801FEA10(u32);
extern void fn_801FE934(u32, int);
extern int fn_801FE900(u32);
extern void fn_801FDFB4(u32, int);
extern u32 fn_8015C910(void);

int fn_801FDC24(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    fn_801FDDB0(id);
    if (entry != 0) {
        if (entry->adjustment == 0x7FFF) {
            if (entry->counter != 0) {
                entry->counter -= 0x7FFF;
            }
            entry->adjustment = 0;
            entry->timer = 0;
        }

        if (entry->adjustment >= entry->counter && entry->counter != 0) {
            if (entry->remaining > 0) {
                if (entry->state == 1) {
                    entry->state = 3;
                    fn_801FEA44(id);
                }
                if (fn_801FE05C(id)) {
                    entry->state = 2;
                }
            } else {
                fn_801FDE24(id);
            }
        } else {
            int value = fn_801FEA10(id);
            if ((s8)value <= 0) {
                fn_801FDE24(id);
            } else {
                fn_801FE934(id, value - 1);
                if ((s8)(value - 1) == 0) {
                    int next = fn_801FE900(id);
                    fn_801FDFB4(id, next);
                }
                fn_801FDE24(id);
            }
        }

        if (fn_8015C910() != 0 && entry->counter != 0) {
            entry->counter++;
            if (entry->counter == 0xFFFF && entry->adjustment != 0) {
                entry->counter -= entry->adjustment;
                entry->adjustment = 0;
                entry->timer = 0;
            }
        }
    }
    return 0;
}
