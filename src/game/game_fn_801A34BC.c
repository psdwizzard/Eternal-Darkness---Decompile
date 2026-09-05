typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ShortCoord3 {
    u32 word;
    u16 half;
} ShortCoord3;

extern u32 lbl_80651E70;
extern u16 lbl_80651E74;
extern u32 lbl_80651E78;
extern u16 lbl_80651E7C;
extern void fn_80180554(void*, void*, void*, void*, u16, int);
extern void* memcpy(void*, const void*, unsigned long);
extern const float lbl_80650D1C;
extern const double lbl_80650D20;

void fn_801A34BC(u8* object, u8* descriptor)
{
    u8* cursor;
    int count;
    int i;
    u8* entry;
    ShortCoord3 second;
    ShortCoord3 first;
    ShortCoord3 copied;

    second.word = lbl_80651E70;
    second.half = lbl_80651E74;
    first.word = lbl_80651E78;
    first.half = lbl_80651E7C;
    entry = *(u8**)(object + 0x4c);
    cursor = descriptor;
    count = descriptor[0];
    i = 0;
    while (i < count) {
        u8* source = *(u8**)(descriptor + 0x14) + *(u16*)(cursor + 0x24) * 0x18;
        copied.word = *(u32*)source;
        copied.half = *(u16*)(source + 4);
        fn_80180554(entry, &copied, &first, &second,
                    *(u16*)(descriptor + 8), 0);
        entry += 0x38;
        cursor += 2;
        i++;
    }

    object[0xe2] = 0;
    *(float*)(object + 0x8c) = *(float*)(descriptor + 0x18);
    *(void**)(object + 0x98) = *(void**)(descriptor + 0x14);
    *(u16*)(object + 0xe0) = *(u16*)(descriptor + 0x64);
    object[0xe3] = descriptor[0x67];
    *(u32*)(object + 0x9c) = *(u32*)(descriptor + 0x20);
    if (descriptor[0x66] != 0) {
        *(float*)(object + 0x90) = lbl_80650D1C;
        *(float*)(object + 0x94) = *(float*)(object + 0x8c) / descriptor[0x66];
    } else {
        *(float*)(object + 0x90) = *(float*)(object + 0x8c);
    }
    memcpy(object + 0xa0, descriptor + 0x24, 0x40);
}
