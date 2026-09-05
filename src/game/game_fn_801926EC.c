typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef union Colour {
    u8 channels[4];
    u32 packed;
} Colour;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern s32 lbl_8064D18C;
extern void fn_801929A4(void);
extern void* fn_80201814(void*);
extern s32 fn_800FBFB0(void);
extern void fn_8014D478(void*, Vec3*, Vec3*, s32, s32, void*, s32);

s32 fn_801926EC(u8* object)
{
    Colour colour;
    Vec3 position;
    Vec3 offset;
    u8* entry;
    s32 i;
    s32 count;
    s32 j;
    u16 value;

    if (*(s32*)(object + 0x38) != lbl_8064D18C ||
        fn_80201814(*(void**)(object + 0xC8)) == 0 ||
        **(s32**)(object + 0xD8) != 0) {
        *(u16*)(object + 0x22) = 8;
    } else if (*(s32*)(object + 0xB8) != 0) {
        entry = *(u8**)(object + 0x4C);
        *(void (**)(void))(object + 0x14C) = fn_801929A4;
        count = object[1] >> 1;
        for (i = 0; i < count; i++) {
            *(u16*)(entry + 8) = *(u16*)(object + 0xA);
            entry += 0x38;
        }
        value = (u16)(count + *(u16*)(object + 0xA));
        for (j = count; j < object[1]; j++) {
            *(u16*)(entry + 8) = value;
            entry += 0x38;
        }

        if (*(s32*)(object + 0xBC) != 0) {
            colour.packed = *(u32*)(object + 0xDC);
            position.x = *(s16*)(object + 0x10);
            position.y = *(s16*)(object + 0x12);
            position.z = *(s16*)(object + 0x14);
            offset.x = *(s16*)(object + 0xC0) - *(s16*)(object + 0x10);
            offset.y = *(s16*)(object + 0xC2) - *(s16*)(object + 0x12);
            offset.z = *(s16*)(object + 0xC4) - *(s16*)(object + 0x14) + 100;
            switch (object[0xB6]) {
            case 1:
                colour.channels[0] -= fn_800FBFB0() & 0x1F;
                break;
            case 2:
                colour.channels[1] -= fn_800FBFB0() & 0x1F;
                break;
            case 3:
                colour.channels[2] -= fn_800FBFB0() & 0x1F;
                break;
            }
            fn_8014D478((void*)0, &position, &offset, 0, 1, colour.channels, 5);
        }
    }
    (*(u16*)(object + 0xA))++;
    return 0;
}
