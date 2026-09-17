typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void fn_80106B34(void*);
extern u32 fn_80106AC0(void*);
extern void* memset(void*, int, unsigned long);

#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define U16(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32(p, o) (*(u32*)((u8*)(p) + (o)))
#define ALIGN32(x) (((x) + 31) & ~31)

int fn_80109424(void* state, u32 base)
{
    u16 width;
    u16 height;
    u32 arena_size;
    u8 x_tiles;
    u8 y_tiles;
    u32 row_size;
    u32 pixels;
    u32 dimensions;
    u32* s = (u32*)state;

    if (state == 0) {
        return 1;
    }

    width = U16(state, 0xA4);
    height = U16(state, 0xA6);
    x_tiles = U8(state, 0xA8);
    y_tiles = U8(state, 0xA9);
    arena_size = ((ALIGN32(U32(state, 0x30)) + 0xFFF) >> 12) * 0x1C000;

    fn_80106B34((u8*)state + 0xA0);
    U32(state, 0x164) = base + ALIGN32(fn_80106AC0((u8*)s + 0xA0));
    U32(state, 0x168) = U32(state, 0x164) + ALIGN32(U32(state, 0x28));
    memset((void*)U32(state, 0x168), 0, arena_size);

    pixels = x_tiles * y_tiles;
    U32(state, 0xD0) = U32(state, 0xE8) = U32(state, 0x154) =
        U32(state, 0x168) + ALIGN32(U32(state, 0x30));
    U32(state, 0x158) = U32(state, 0x160) = U32(state, 0x154);
    U32(state, 0xD4) = U32(state, 0xEC) = U32(state, 0x15C) =
        U32(state, 0xF0) = U32(state, 0x154) + arena_size;

    dimensions = width * height;
    row_size = ALIGN32((dimensions * (pixels + 2)) / pixels);
    U32(state, 0xFC) = U32(state, 0xF0) + row_size;
    U32(state, 0x108) = U32(state, 0xFC) + row_size;
    U32(state, 0x114) = U32(state, 0x108) + row_size;
    U32(state, 0x120) = U32(state, 0x114) + row_size;
    U32(state, 0x12C) = U32(state, 0x120) + row_size;
    return 0;
}
