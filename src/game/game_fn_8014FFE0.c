typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3Words { u32 x, y, z; } Vec3Words;

extern int lbl_8064D18C;
extern void fn_80149E28(void*);
extern void fn_8014FCF4(Vec3Words*, s16, u16, u32, u32*);
extern void fn_8014F9D4(Vec3Words*, s16, u16, u32, u32*, float);

#pragma opt_propagation off
void fn_8014FFE0(u8* instance)
{
    if (*(int*)(instance + 0x1324) != lbl_8064D18C) {
        fn_80149E28(instance);
        return;
    }
    switch (*(u16*)(instance + 0x132C)) {
    case 2: {
        u32 source = *(u32*)(instance + 0x20);
        fn_8014FCF4((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source);
        break;
    }
    case 12: {
        u32 source = *(u32*)(instance + 0x20);
        fn_8014FCF4((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source);
        break;
    }
    case 22: {
        u32 source = *(u32*)(instance + 0x20);
        fn_8014FCF4((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source);
        break;
    }
    case 32: {
        u32 source = *(u32*)(instance + 0x20);
        float scale = *(float*)(instance + 0x1C);
        fn_8014F9D4((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source,
                    scale);
        break;
    }
    case 47: {
        u32 source = *(u32*)(instance + 0x20);
        float scale = *(float*)(instance + 0x1C);
        fn_8014F9D4((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source,
                    scale);
        break;
    }
    case 62: {
        u32 source = *(u32*)(instance + 0x20);
        float scale = *(float*)(instance + 0x1C);
        fn_8014F9D4((Vec3Words*)(instance + 0x10), *(s16*)(instance + 0x0E),
                    *(u16*)(instance + 0x0C), *(u32*)(instance + 8), &source,
                    scale);
        break;
    }
    case 91:
        fn_80149E28(instance);
        break;
    }
}
#pragma opt_propagation reset
