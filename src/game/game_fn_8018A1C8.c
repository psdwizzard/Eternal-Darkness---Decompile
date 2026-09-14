typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern int lbl_8064D738;
extern u8 lbl_80607120[];
extern void fn_8018D724(void*, void*, void*);
extern void fn_80188A7C(void*, void*, void (*)(void*, void*, void*));
extern void DCFlushRange(void*, unsigned long);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_801887C4(void*, void*, void*);

void fn_8018A1C8(u8* object)
{
    register u8* self;
    register u8* buffer2;
    register u8* buffer1;
    register u8* buffer0;
    int offset;
    int i;
    u8 count;
    u16 size0;
    u16 size1;
    u16 size2;
    u8* entry;
    u8* out;
    u16 vertex_count;

    self = object;
    count = self[1];
    vertex_count = *(u16*)(lbl_80607120 + 2);
    size0 = *(u16*)(lbl_80607120 + 0xA);
    size1 = *(u16*)(lbl_80607120 + 0xE);
    size2 = *(u16*)(lbl_80607120 + 0xC);
    buffer0 = *(u8**)(self + 0x50);
    buffer1 = *(u8**)(self + 0x54);
    buffer2 = *(u8**)(self + 0x58);

    if (lbl_8064D738 != 0) {
        buffer1 += vertex_count * 4;
        buffer0 += vertex_count * 6;
        buffer2 += vertex_count * 4;
    }
    entry = *(u8**)(self + 0x4C);
    out = buffer2;
    i = 0;
    offset = 0;
    for (; i < count; i++) {
        int j;
        fn_80188A7C(entry, buffer0 + offset, fn_8018D724);
        for (j = 0; j < entry[0x20]; j++) {
            out[0] = entry[0x28];
            out[1] = entry[0x29];
            out[2] = entry[0x2A];
            out[3] = entry[0x2B];
            out += 4;
        }
        entry += 0x38;
        offset += 0xC;
    }
    {
        int saved = fn_801ED57C(0);
        DCFlushRange(buffer0, size0);
        DCFlushRange(buffer2, size2);
        DCFlushRange(buffer1, size1);
        fn_8018D0D0(self, self + 0x5C, *(s16*)(self + 0xE));
        fn_801887C4(buffer0, buffer1, buffer2);
        fn_801ED57C(saved);
    }
}
