typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;

extern int fn_80180430(void*, u8);
extern void fn_80180518(void*, u8, int);
extern void fn_8017DCA8(void*, s16, void*);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8018E230(void*, void*, int, u8, u8, int);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);

#pragma opt_propagation off
int fn_8019C06C(u8* object)
{
    u8* cursor;
    int frame;
    u16 count;
    u8* slot;
    u8* base;
    u8* source;
    int i;

    base = object + 0x8c;
    i = 0;
    frame = (s16)*(float*)(object + 0xcc);
    source = *(u8**)(object + 0x4c);
    count = object[1];
    cursor = base;

    for (; i < count; i++) {
        if (fn_80180430(object + 0x24, (u8)i)) {
            fn_8017DCA8(source + 0xa, *(s16*)(source + 0x1c), source + 0x10);
            slot = base + i;
            if (*(s16*)(source + 0x14) < (s8)slot[0] ||
                *(s16*)(source + 0x14) >= (s8)slot[8]) {
                *(s16*)(source + 0x1c) = -*(s16*)(source + 0x1c);
            }

            if (source[0] != 0) {
                if (!fn_8018E26C(source, source + 0x2b)) {
                    *(u16*)(cursor + 0x28) = 0;
                    fn_80180518(object + 0x24, (u8)i, 0);
                }
            } else if ((s16)(*(s16*)(source + 0xe) - frame) <= 60 &&
                       (slot[0x20] & 2) == 0) {
                fn_8018E230(source, source + 0x2b, 1, object[2], object[4], 0);
                slot[0x20] |= 2;
            }
        } else {
            if (source[0] != 0) {
                if (!fn_8018E26C(source, source + 0x2b)) {
                    fn_80180518(object + 0x24, (u8)i, 1);
                    fn_801B05E8(0x11, 0x37, 1, 1, 0, 5, 0, 0);
                }
            }

            if (*(u16*)(cursor + 0x28) != 0) {
                --*(u16*)(cursor + 0x28);
                if (*(u16*)(cursor + 0x28) == 0) {
                    fn_8018E230(source, source + 0x2b, 1, 0, 1, 250);
                }
            }
        }
        source += 0x38;
        cursor += 2;
    }

    ++*(u16*)(object + 0xa);
    if (*(u16*)(object + 0xa) >= *(u16*)(object + 0xc)) {
        *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
#pragma opt_propagation reset
