typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern int lbl_8064D738;
extern u8 lbl_80607120[];
extern u8 lbl_80606AE0[];
extern void* lbl_8064D24C;

extern void fn_8018D688(void*, void*, void*);
extern void fn_80188A7C(void*, void*, void (*)(void*, void*, void*));
extern void DCFlushRange(void*, unsigned long);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern int fn_8017FFB8(void), fn_8017FFB0(void), fn_8017FF98(void);
extern void fn_80225F4C(int, void*, u8);
extern void fn_8022B448(void*, void*);

void fn_8018A060(u8* arg)
{
    u8* data;
    u16 vertex_count;
    u8* buffer0;
    u8* buffer1;
    u8* buffer2;
    u8* object;
    int buffer_offset;
    int i;
    u8 entry_count;
    u16 buffer0_size;
    u16 buffer1_size;
    u16 buffer2_size;
    u8* entry;
    u8* color_out;

    object = arg;
    data = lbl_80607120;
    entry_count = object[1];
    vertex_count = *(u16*)(data + 2);
    buffer0_size = *(u16*)(data + 0xA);
    buffer1_size = *(u16*)(data + 0xE);
    buffer2_size = *(u16*)(data + 0xC);
    buffer0 = *(u8**)(object + 0x50);
    buffer1 = *(u8**)(object + 0x54);
    buffer2 = *(u8**)(object + 0x58);
    if (lbl_8064D738 != 0) {
        buffer1 += vertex_count * 4;
        buffer0 += vertex_count * 6;
        buffer2 += vertex_count * 4;
    }

    entry = *(u8**)(object + 0x4C);
    color_out = buffer2;
    i = 0;
    buffer_offset = 0;
    for (; i < entry_count; i++) {
        int j;
        fn_80188A7C(entry, buffer0 + buffer_offset, fn_8018D688);
        for (j = 0; j < entry[0x20]; j++) {
            color_out[3] = entry[0x2B];
            color_out += 4;
        }
        entry += 0x38;
        buffer_offset += 0xC;
    }

    DCFlushRange(buffer0, buffer0_size);
    DCFlushRange(buffer2, buffer2_size);
    DCFlushRange(buffer1, buffer1_size);
    {
        int saved = fn_801ED57C(0);
        fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
        fn_80225F4C(9, buffer0, (u8)fn_8017FFB8());
        fn_80225F4C(0xB, buffer2, (u8)fn_8017FF98());
        fn_80225F4C(0xD, buffer1, (u8)fn_8017FFB0());
        fn_8022B448(lbl_80606AE0, lbl_8064D24C);
        fn_801ED57C(saved);
    }
}
