typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 fn_80180430(void*, u8);
extern s32 fn_80180454(void*);
extern void fn_80180518(void*, u8, s32);
extern void fn_8017E1B0(void*, void*);
extern void fn_8018E26C(void*, void*);
extern void fn_8018E230(void*, void*, s32, s32, u8, u8);
extern void* fn_8017FDA8(void*, s32);
extern u32 fn_800FBFB0(void);
extern void* memcpy(void*, const void*, u32);

s32 fn_8019A5DC(u8* object)
{
    u8 count;
    u8* entry;
    s32 i;

    i = 0;
    entry = *(u8**)(object + 0x4C);
    count = object[1];
    while (i < count) {
        if (fn_80180430(object + 0x24, (u8)i) != 0) {
            fn_8017E1B0(entry + 0xA, entry + 0x10);
            if (entry[0] != 0) {
                fn_8018E26C(entry, entry + 0x2B);
            } else if (*(s32*)(object + 0x8C) == 0 ||
                       *(u16*)(object + 0xA) >= *(u16*)(object + 0xC)) {
                if (entry[0x2B] == 0) {
                    fn_80180518(object + 0x24, (u8)i, 0);
                } else {
                    fn_8018E230(entry, entry + 0x2B, 1,
                                object[2], object[4], 0);
                }
            } else if (*(u16*)(object + 0xA) == *(u16*)(entry + 8)) {
                fn_8018E230(entry, entry + 0x2B, 1,
                            object[2], object[4], 0);
            } else if (entry[0x2B] == 0) {
                void* source = fn_8017FDA8(*(void**)(object + 0x9C), 0);
                memcpy(entry + 0xA, source, 6);
                *(u16*)(entry + 0x10) = 4 - (fn_800FBFB0() & 7);
                *(u16*)(entry + 0x12) = 4 - (fn_800FBFB0() & 7);
                *(u16*)(entry + 0x14) = 4 - (fn_800FBFB0() & 3);
                *(u16*)(entry + 8) = *(u16*)(object + 0xA) +
                                     7 + (fn_800FBFB0() & 7);
                fn_8018E230(entry, entry + 0x2B, 1, 0, 0x33, 0xFF);
            }
        }
        entry += 0x38;
        i++;
    }
    if (fn_80180454(object + 0x24) != 0 ||
        *(u16*)(object + 0xA) > 10000) {
        *(u16*)(object + 0x22) = 8;
    }
    (*(u16*)(object + 0xA))++;
    return 0;
}
