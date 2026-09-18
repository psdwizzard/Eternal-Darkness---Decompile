typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_80651D98;
extern u16 lbl_80651D9C;
extern u32 lbl_80650B24;
extern void* memcpy(void*, const void*, u32);

void fn_801913F4(u8* object)
{
    u32 value = lbl_80650B24;
    // Keep the observable spill while allowing the plain view to reuse value.
    union SavedValue {
        volatile u32 observable;
        u32 plain;
    } saved_value;
    struct LocalValues {
        u32 word;
        u16 half;
    } source;

    source.word = lbl_80651D98;
    source.half = lbl_80651D9C;
    object[0] = 0x20;
    object[1] = 1;
    {
        u8 first = object[0];
        saved_value.observable = value;
        *(u16*)(object + 6) = first;
    }
    *(u16*)(object + 4) = 0x31;
    object[2] = 0x87;
    *(signed char*)(object + 3) = -9;
    *(u32*)(object + 0xC) = 0;
    object[0x14] = 2;
    object[0x15] = 1;
    object[0x16] = 9;
    object[0x17] = 4;
    object[0x18] = 1;
    object[0x19] = 200;
    object[0x1A] = 10;
    object[0x1B] = 5;
    object[0x1C] = 1;
    object[0x1D] = 0;
    *(u32*)(object + 0x28) = 0;
    *(u32*)(object + 0x2C) = 0;
    *(u32*)(object + 0x38) = 0;
    memcpy(object + 0x1E, &source, 6);
    *(u32*)(object + 0x3C) = saved_value.plain;
    object[0x24] = 0;
}
