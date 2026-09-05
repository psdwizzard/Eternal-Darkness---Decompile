typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3Words { u32 x, y, z; } Vec3Words;

extern int lbl_8064D18C;
extern void fn_80149E28(void*);
extern void fn_8014F834(Vec3Words*, s16, u16, u32, u32*, float);
extern void fn_8014FB80(Vec3Words*, s16, u16, u32, u32*);

#pragma opt_propagation off
void fn_8014FE64(u8* instance)
{
    if (*(int*)(instance + 0x1324) != lbl_8064D18C) {
        fn_80149E28(instance);
        return;
    }
    switch (*(u16*)(instance + 0x132C)) {
    case 30: {
        u32 source = *(u32*)(instance + 0x20);
        float scale = *(float*)(instance + 0x1C);
        fn_8014F834((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source,
                    scale);
        break;
    }
    case 45: {
        u32 source = *(u32*)(instance + 0x20);
        float scale = *(float*)(instance + 0x1C);
        fn_8014F834((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source,
                    scale);
        break;
    }
    case 60: {
        u32 first_source = *(u32*)(instance + 0x20);
        float scale = *(float*)(instance + 0x1C);
        fn_8014F834((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &first_source,
                    scale);
        {
        u32 second_source = *(u32*)(instance + 0x20);
        fn_8014FB80((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &second_source);
        }
        break;
    }
    case 70: {
        u32 source = *(u32*)(instance + 0x20);
        fn_8014FB80((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source);
        break;
    }
    case 80: {
        u32 source = *(u32*)(instance + 0x20);
        fn_8014FB80((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source);
        break;
    }
    case 82:
        fn_80149E28(instance);
        break;
    }
}
#pragma opt_propagation reset
