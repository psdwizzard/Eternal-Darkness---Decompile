typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 HVQM4BuffSize(void*);

#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define U16(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32(p, o) (*(u32*)((u8*)(p) + (o)))
#define ALIGN32(x) (((x) + 31) & ~31)

u32 fn_80109574(void* state)
{
    u32 result;

    if (state == 0) {
        return 1;
    }

    result = ALIGN32(U32(state, 0x28));
    result += ALIGN32(U32(state, 0x30));
    result += (((ALIGN32(U32(state, 0x30)) + 0xFFF) >> 12) * 0x1C000);
    result += ALIGN32(((u32)U16(state, 0xA4) * U16(state, 0xA6) *
                      (U8(state, 0xA8) * U8(state, 0xA9) + 2)) /
                     (U8(state, 0xA8) * U8(state, 0xA9))) * 6;
    result += ALIGN32(HVQM4BuffSize((u8*)state + 0xA0));
    return result;
}
