typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

extern int lbl_8064D18C;
extern void* memset(void*, int, unsigned long);
extern void fn_801991E0(void*, void*, int);
extern int fn_80199108(void*);
extern u32 rand(void);
extern void fn_8018E230(void*, void*, int, u8, u8, u8);
extern void fn_8018E260(void*, u8, u8);
extern void fn_80180518(void*, u8, int);
extern void fn_8019916C(void*, void*);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8017DCA8(void*, s16, void*);
extern int fn_80180454(void*);
extern void fn_8018EA58(void*);

int fn_80199B84(u8* object)
{
    int count;
    u8* entry;
    int index;

    count = object[1];
    if (*(int*)(object + 0x38) != lbl_8064D18C) {
        memset(object + 0x24, 0, 0x10);
        entry = *(u8**)(object + 0x4c);
        for (index = 0; index < count; index++) {
            entry[0x2b] = 0;
        }
        *(int*)(object + 0x38) = lbl_8064D18C;
    }

    if (*(int*)(object + 0xa0) != 0) {
        fn_801991E0(object, object + 0xbc, 8);
    } else {
        if (*(int*)(object + 0xa4) != 0 ||
            *(u16*)(object + 0xa) < *(u16*)(object + 0xc)) {
            if (fn_80199108(object) != 0) {
                entry = *(u8**)(object + 0x4c) + object[0x91] * 0x38;
                fn_8018E230(entry, entry + 0x2b, 2,
                            (u8)(rand() % 8 * 10 + 180),
                            object[4], object[0x90]);
                fn_8018E260(entry, object[0x8f], object[0x90]);
                fn_80180518(object + 0x24, object[0x91], 1);
                object[0x91]++;
                if (object[0x91] >= object[0x8d]) {
                    *(u32*)(object + 0x98) = 0;
                    object[0x91] = 0;
                }
                fn_8019916C(object, 0);
            } else {
                u16 frame = *(u16*)(object + 0xa);
                if (frame % object[0x8c] == 0) {
                    *(u32*)(object + 0x98) = 1;
                }
            }
        }

        entry = *(u8**)(object + 0x4c);
        for (index = 0; index < count; index++) {
            if (entry[0] != 0) {
                if (!fn_8018E26C(entry, entry + 0x2b)) {
                    fn_80180518(object + 0x24, (u8)index, 0);
                }
                fn_8017DCA8(entry + 0xa, *(s16*)(entry + 0x1c), entry + 0x10);
            }
            entry += 0x38;
        }
        if (*(int*)(object + 0xa4) == 0 &&
            *(u16*)(object + 0xa) >= *(u16*)(object + 0xc) &&
            fn_80180454(object + 0x24)) {
            *(u16*)(object + 0x22) = 8;
            *(u32*)(object + 0x98) = 0;
        }
    }
    (*(u16*)(object + 0xa))++;
    fn_8018EA58(object);
    return 0;
}
