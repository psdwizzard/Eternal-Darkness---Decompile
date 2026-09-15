typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern unsigned int fn_80178F14(s16, s16, s16, int, int, int);
extern int fn_80180430(void*, u8);
extern int fn_80180454(void*, u16);
extern void fn_80180518(void*, u8, int);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8018EFB0(void*, int, int);
extern void fn_8017D2B4(void*, void*, void*);
extern unsigned int fn_800FBFB0(void);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern float lbl_8063D378[];

int fn_8017F3B4(u8* object)
{
    int offset;
    u8* state_cursor;
    int limit;
    u8* pair;
    u8* entry;
    u8* state;
    u8 count;
    int amount;
    int vertical;
    int index;
    int special;

    amount = 0xFF;
    state = object + 0x8C;
    vertical = -1;
    special = 0;
    count = object[1];

    if (fn_80178F14(*(s16*)(object + 0x10), *(s16*)(object + 0x12),
                     *(s16*)(object + 0x14), (int)lbl_8063D378[0],
                     (int)lbl_8063D378[1], (int)lbl_8063D378[2]) < 0x208) {
        special = 1;
        amount = 250;
        vertical = -10;
    }

    index = 0;
    offset = 0;
    state_cursor = state;
    limit = count - 1;
    for (; index < count; offset += 0x38, state_cursor += 4, index++) {
        entry = *(u8**)(object + 0x4C) + offset;
        if (fn_80180430(object + 0x24, (u8)index)) {
            if (entry[0] && !fn_8018E26C(entry, entry + 0x2B) && !entry[1]) {
                fn_80180518(object + 0x24, (u8)index, 0);
            }
            if ((*(u16*)(object + 0x0A) & 3) == 0 && (index & 1) == 0 && index < limit) {
                pair = state + index;
                pair[0]++;
                pair[1]++;
                if (pair[0] >= pair[0x10]) {
                    *(s16*)(entry + 0x16) = 0;
                    *(s16*)(entry + 0x18) = 0;
                    *(s16*)(entry + 0x10) = *(s16*)(object + 0x16);
                    *(s16*)(entry + 0x12) = *(s16*)(object + 0x18);
                    fn_8018EFB0(entry + 0x10, 2, 0);
                    fn_8018EFB0(entry + 0x10, 2, 1);
                    if (*(s16*)(entry + 0x10) != 0)
                        *(s16*)(entry + 0x16) = *(s16*)(entry + 0x10) > 0 ? -1 : 1;
                    if (*(s16*)(entry + 0x12) != 0)
                        *(s16*)(entry + 0x18) = *(s16*)(entry + 0x12) > 0 ? -1 : 1;
                    *(int*)(state_cursor + 0x20) ^= 1;
                    pair[0] = 0;
                    if (*(int*)(state_cursor + 0x20)) {
                        *(s16*)(entry + 0x1A) = -1;
                        pair[0x10] = (fn_800FBFB0() & 3) + 1;
                    } else {
                        *(s16*)(entry + 0x1A) = 0;
                        pair[0x10] = (fn_800FBFB0() & 15) + 0x20;
                    }
                    pair[0x11] = pair[0x10];
                    *(int*)(state_cursor + 0x24) = *(int*)(state_cursor + 0x20);
                    pair[1] = pair[0];
                }
                fn_8017D2B4(entry + 0x0A, entry + 0x16, entry + 0x10);
                if (*(s16*)(entry + 0x10) == 0) *(s16*)(entry + 0x16) = 0;
                if (*(s16*)(entry + 0x12) == 0) *(s16*)(entry + 0x18) = 0;
                if (*(s16*)(entry + 0x14) < -1 || *(s16*)(entry + 0x14) >= 0)
                    *(s16*)(entry + 0x1A) = -*(s16*)(entry + 0x1A);
                *(s16*)(entry + 0x42) = *(s16*)(entry + 0x0A) + entry[0x22] * 4;
                *(s16*)(entry + 0x44) = *(s16*)(entry + 0x0C) + entry[0x22] * 4;
                *(s16*)(entry + 0x46) = *(s16*)(entry + 0x0E);
            }
            if (*(u16*)(object + 0x0A) == *(u16*)(entry + 8) || (special && !entry[0]))
                fn_8018E230(entry, entry + 0x2B, 1, amount, vertical, 0);
        }
    }
    {
        u8* entries = *(u8**)(object + 0x4C);
        if (fn_80180454(object + 0x24, (*(u16*)(object + 0x0A))++) ||
            *(u16*)(object + 0x0A) > *(u16*)(entries + 8) + 500)
            *(u16*)(object + 0x22) = 8;
    }
    return 0;
}
