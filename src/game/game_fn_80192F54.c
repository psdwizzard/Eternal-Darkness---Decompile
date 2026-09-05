typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern s32 lbl_8064D18C;
extern double lbl_80650B18;
extern float lbl_80650B20;
extern float lbl_80650B4C;
extern void fn_801931C4(void);
extern void* fn_80201814(void*);
extern s32 fn_800FBFB0(void);
extern void fn_8014D478(void*, Vec3*, Vec3*, s32, s32, void*, s32);
extern void fn_8018EA58(void*);

typedef struct Colour {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Colour;

typedef union PackedColour {
    Colour channels;
    u32 packed;
} PackedColour;

#pragma opt_common_subs off
s32 fn_80192F54(u8* object)
{
    float zero;
    Vec3 position;
    Vec3 offset;
    PackedColour colour;
    u8* entry;
    s32 i;
    s32 count;
    s32 j;
    u16 next_time;

    if (*(s32*)(object + 0x38) != lbl_8064D18C ||
        fn_80201814(*(void**)(object + 0xC8)) == 0 ||
        **(s32**)(object + 0xD8) != 0) {
        *(u16*)(object + 0x22) = 8;
    } else if (*(s32*)(object + 0xB8) != 0) {
        entry = *(u8**)(object + 0x4C);
        i = 0;
        *(void (**)(void))(object + 0x14C) = fn_801931C4;
        count = object[1] >> 1;
        while (i < count) {
            *(u16*)(entry + 8) = *(u16*)(object + 0xA);
            entry += 0x38;
            i++;
        }
        next_time = (u16)(count + *(u16*)(object + 0xA));
        j = count;
        while (j < object[1]) {
            *(u16*)(entry + 8) = next_time;
            entry += 0x38;
            j++;
        }

        if (*(s32*)(object + 0xBC) != 0) {
            colour.packed = *(u32*)(object + 0xDC);
            zero = lbl_80650B20;
            position.x = *(s16*)(object + 0x10);
            position.y = *(s16*)(object + 0x12);
            position.z = *(s16*)(object + 0x14);
            offset.x = zero;
            offset.y = zero;
            offset.z = lbl_80650B4C;
            switch (object[0xB6]) {
            case 1:
                colour.channels.red -= fn_800FBFB0() & 0x1F;
                break;
            case 2:
                colour.channels.green -= fn_800FBFB0() & 0x1F;
                break;
            case 3:
                colour.channels.blue -= fn_800FBFB0() & 0x1F;
                break;
            }
            fn_8014D478((void*)0, &position, &offset, 0, 1, &colour.channels, 5);
        }
    }
    (*(u16*)(object + 0xA))++;
    fn_8018EA58(object);
    return 0;
}
#pragma opt_common_subs reset
