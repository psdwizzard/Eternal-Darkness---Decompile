typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

extern s32 lbl_8064D18C;
extern s32 fn_800FBFB0(void);
extern s32 fn_80180430(void*, u8);
extern s32 fn_80180454(void*);
extern void fn_80180518(void*, u8, s32);
extern s32 fn_80179064(s16, s16, s16, s16);
extern void fn_8017DA60(void*, void*, void*, u8);
extern void fn_8017D318(void*, void*, s16, void*, u8, u8);
extern void fn_8017E1B0(void*, void*);
extern s32 fn_8017E2B0(void*, void*, u8);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8018E230(void*, void*, s32, u8, u8, s32);
extern void fn_801795D8(void*, void*, void*);
extern void fn_80179904(void*, s32);
extern void fn_8014D478(s32, float*, float*, s32, s32, u8*, s32);
extern void* fn_80201814(void*);
extern void* memcpy(void*, const void*, unsigned long);

s32 fn_801929A4(u8* argument)
{
    u8 colour[4];
    float position[3];
    float offset[3];
    s32 count;
    u8 variant;
    u8* entry;
    s32 i;
    u8 saved;
    u8* object;
    u8* flags;

    object = argument;
    if (*(s32*)(object + 0x38) == lbl_8064D18C) {
        variant = object[0xAC];
        flags = object + 0x8C;
        entry = *(u8**)(object + 0x4C);
        i = 0;
        count = object[1];
        while (i < count) {
            if (fn_80180430(object + 0x24, (u8)i)) {
                saved = flags[i];
                if ((*(u16*)(object + 0xA) & object[0xB2]) == 0) {
                    s32 distance = fn_80179064(*(s16*)(entry + 0xA), *(s16*)(entry + 0xC),
                                               *(s16*)(object + 0xC0), *(s16*)(object + 0xC2));
                    if (distance < 160) {
                        entry[0x21] = (distance >> 5) + 2;
                    } else {
                        u16 value = (u16)(320 - *(u16*)(entry + 8) + *(u16*)(object + 0xA));
                        if (value <= 36)
                            entry[0x21] = value / 6 + 1;
                    }
                    if ((s32)(*(u16*)(entry + 8) - *(u16*)(object + 0xA)) < 290) {
                        fn_8017DA60(entry + 0xA, object + 0xC0, entry + 0x10, variant);
                    } else if ((s32)(*(u16*)(entry + 8) - *(u16*)(object + 0xA)) < 305) {
                        fn_8017D318(entry + 0xA, object + 0xC0, *(s16*)(entry + 0x1C),
                                   entry + 0x10, flags[i], variant);
                    } else {
                        fn_8017E1B0(entry + 0xA, entry + 0x10);
                    }
                }
                if (fn_8017E2B0(entry + 0xA, object + 0xC0, object[0xB4])) {
                    entry[0x2B] = 0;
                    fn_80180518(object + 0x24, (u8)i, 0);
                } else {
                    flags[i] = saved;
                    if (entry[0] != 0) {
                        if (fn_8018E26C(entry, entry + 0x2B) == 0)
                            fn_80180518(object + 0x24, (u8)i, 0);
                    } else if (*(u16*)(object + 0xA) > *(u16*)(entry + 8) - 15) {
                        fn_8018E230(entry, entry + 0x2B, 1, object[2], object[4], 0);
                    }
                }
            } else if (*(u16*)(object + 0xA) > *(u16*)(entry + 8) &&
                       **(s32**)(object + 0xD8) == 0) {
                *(u16*)(entry + 8) += 320;
                memcpy(entry + 0xA, object + 0x10, 6);
                fn_801795D8(object + 0xC0, object + 0x10, entry + 0x10);
                fn_80179904(entry + 0x10, 16);
                *(s16*)(entry + 0x10) += 16 - (fn_800FBFB0() & 0x1F);
                *(s16*)(entry + 0x12) += 16 - (fn_800FBFB0() & 0x1F);
                *(s16*)(entry + 0x14) += 18 - (fn_800FBFB0() & 7);
                fn_80179904(entry + 0x10, (s16)(object[0xB1] + (fn_800FBFB0() & 7)));
                entry[0x2B] = object[2];
                fn_80180518(object + 0x24, (u8)i, 1);
            }
            entry += 0x38;
            i++;
        }

        if (*(s32*)(object + 0xBC) != 0 && (*(u16*)(object + 0xA) & 0xF) == 0) {
            *(s32*)colour = *(s32*)(object + 0xDC);
            position[0] = *(s16*)(object + 0x10);
            position[1] = *(s16*)(object + 0x12);
            position[2] = *(s16*)(object + 0x14);
            offset[0] = 16 - (fn_800FBFB0() & 0x1F);
            offset[1] = 16 - (fn_800FBFB0() & 0x1F);
            offset[2] = 18 - (fn_800FBFB0() & 7);
            switch (object[0xB6]) {
            case 1: colour[0] -= fn_800FBFB0() & 0x1F; break;
            case 2: colour[1] -= fn_800FBFB0() & 0x1F; break;
            case 3: colour[2] -= fn_800FBFB0() & 0x1F; break;
            }
            fn_8014D478(0, position, offset, 0, 1, colour, 8);
        }
        if (**(s32**)(object + 0xD8) != 0 && fn_80180454(object + 0x24) != 0)
            *(u16*)(object + 0x22) = 8;

        if (object[0x60] != 0) {
            if (fn_8018E26C(object + 0x60, object + 0x5F) == 0)
                *(u16*)(object + 0x22) = 8;
        } else if (fn_80201814(*(void**)(object + 0xC8)) == 0) {
            fn_8018E230(object + 0x60, object + 0x5F, 1, object[2], object[4], 0);
        }
    } else {
        *(u16*)(object + 0x22) = 8;
    }
    (*(u16*)(object + 0xA))++;
    return 1;
}
