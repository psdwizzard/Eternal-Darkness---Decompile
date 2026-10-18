typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_80650C14;
extern u16 lbl_80650C18;
extern u32 rand(void);
extern void fn_8019C26C(void*, void*, void*, void*, void*);

void fn_8019BFA0(u8* object)
{
    int offset;
    u8* cursor;
    u8* element;
    int i;
    u8 count;
    u8* base;
    u8* source;
    struct {
        u32 word;
        u16 half;
    } setup;

    base = object + 0x8c;
    setup.word = lbl_80650C14;
    setup.half = lbl_80650C18;
    source = *(u8**)(object + 0x4c);
    count = object[1];
    fn_8019C26C(object + 0x10, &setup, base + 0x44, base + 0x68,
                base + 0x38);

    cursor = base;
    i = 0;
    offset = 0;
    for (; i < count; i++) {
        u32 random = rand();
        element = base + i;
        *(u16*)(cursor + 0x28) = offset + (random & 0x1f);
        element[0] = *(s16*)(source + 0x14);
        element[8] = element[0] + 1;
        element[0x10] = 0;
        element[0x18] = (rand() & 7) + 25;
        element[0x20] = 0;
        source += 0x38;
        offset += 0x80;
        cursor += 2;
    }
}
