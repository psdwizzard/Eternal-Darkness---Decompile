typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern s32 lbl_8064D18C;

extern u32 rand(void);
extern void fn_8017E1B0(void*, void*);
extern int fn_80180430(void*, u8);
extern int fn_80180454(void*);
extern void fn_80180518(void*, u8, int);
extern void fn_8018E230(void*, void*, int, u8, u8, u8);
extern void fn_8018E26C(void*, void*);

int fn_8019AAF0(u8* object)
{
    u8* entry;
    u8 count;
    int i;

    if ((*(u16*)(object + 0xA) & object[0x97]) == 0) {
        count = object[1];
        if ((*(u16*)(object + 0xA) & object[0x98]) == 0 &&
            object[0x96] < count) {
            entry = *(u8**)(object + 0x4C) + object[0x96] * 0x38;
            fn_8018E230(entry, entry + 0x2B, 1, 0, 0x33, 0xFF);
            fn_80180518(object + 0x24, object[0x96], 1);
            object[0x96]++;
        }

        entry = *(u8**)(object + 0x4C);
        for (i = 0; i < count; entry += 0x38, i++) {
            if (fn_80180430(object + 0x24, (u8)i)) {
                fn_8017E1B0(entry + 0xA, entry + 0x10);
                if (entry[0] != 0) {
                    fn_8018E26C(entry, entry + 0x2B);
                } else if (*(u16*)(object + 0xA) >= *(u16*)(object + 0xC)) {
                    if (entry[0x2B] == 0) {
                        fn_80180518(object + 0x24, (u8)i, 0);
                    } else {
                        fn_8018E230(entry, entry + 0x2B, 1, entry[0x2B],
                                    object[4], 0);
                    }
                } else if (*(u16*)(object + 0xA) >= *(u16*)(entry + 8)) {
                    if (entry[0x2B] == 0) {
                        *(u16*)(entry + 0xA) = *(s16*)(object + 0x10) +
                            *(u32*)(object + 0x8C) -
                            (*(u32*)(object + 0x90) & rand());
                        *(u16*)(entry + 0xC) = *(s16*)(object + 0x12) +
                            *(u32*)(object + 0x8C) -
                            (*(u32*)(object + 0x90) & rand());
                        *(u16*)(entry + 0xE) = *(s16*)(object + 0x14);
                        *(u16*)(entry + 0x14) = *(s16*)(object + 0x1A) +
                            (rand() & 3);
                        *(u16*)(entry + 8) = *(u16*)(object + 0xA) +
                            *(u16*)(object + 0x94) + (rand() & 7);
                        fn_8018E230(entry, entry + 0x2B, 1, 0, 0x33, 0xFF);
                    } else {
                        fn_8018E230(entry, entry + 0x2B, 1, entry[0x2B],
                                    object[4], 0);
                    }
                }
            }
        }
    }

    if (fn_80180454(object + 0x24) || lbl_8064D18C != *(s32*)(object + 0x38)) {
        *(u16*)(object + 0x22) = 8;
    }
    (*(u16*)(object + 0xA))++;
    return 0;
}
