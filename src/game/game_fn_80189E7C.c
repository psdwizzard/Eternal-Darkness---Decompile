typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern int lbl_8064D738;
extern float lbl_80650A68;
extern u8 lbl_80607130[];
extern void fn_8018D020(void), fn_8018D400(void*, void*, void*);
extern void fn_80188A7C(void*, void*, void*), DCFlushRange(void*, unsigned long);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16), fn_801ED468(int);
extern int fn_8017FFB8(void), fn_8017FFB0(void), fn_8017FF98(void);
extern void fn_80225F4C(int, void*, u8), fn_801ECEC8(int, int, int);
extern void fn_8018D2E0(float), fn_80226AB4(int, int, u16);
extern void fn_80188578(u16), fn_8018856C(u16), fn_80188560(u16);
extern void fn_8018855C(void), fn_80226D78(int);

void fn_80189E7C(u8* self)
{
    u16 i;
    u8* data;
    u16 count;
    u16 flush0;
    u16 flush1;
    u16 flush2;
    u8* buffer0;
    u8* buffer1;
    u8* buffer2;
    u8* object;
    u8* entries;
    u8* out;
    int saved;
    int j;

    object = self;
    data = lbl_80607130;
    count = *(u16*)(data + 2);
    flush0 = *(u16*)(data + 0xA);
    flush1 = *(u16*)(data + 0xE);
    flush2 = *(u16*)(data + 0xC);
    buffer0 = *(u8**)(object + 0x50);
    buffer1 = *(u8**)(object + 0x54);
    buffer2 = *(u8**)(object + 0x58);

    if (lbl_8064D738 != 0) {
        buffer1 += count * 4;
        buffer0 += count * 6;
        buffer2 += count * 4;
    }
    entries = *(u8**)(object + 0x4C);
    if (*(int*)(object + 0x98) != 0) {
        fn_8018D400(object, buffer0, fn_8018D020);
    } else {
        fn_80188A7C(entries, buffer0, fn_8018D020);
    }
    out = buffer2;
    for (i = 0; i < entries[0x20]; i++) {
        *(int*)out = *(int*)(entries + 0x28);
        out += 4;
    }
    DCFlushRange(buffer0, flush0);
    DCFlushRange(buffer1, flush1);
    DCFlushRange(buffer2, flush2);
    saved = fn_801ED57C(0);
    fn_8018D0D0(object, object + 0x5C, *(s16*)(object + 0xE));
    fn_801ED468(0x3C);
    fn_80225F4C(9, buffer0, (u8)fn_8017FFB8());
    fn_80225F4C(0xD, buffer1, (u8)fn_8017FFB0());
    fn_80225F4C(0xB, buffer2, (u8)fn_8017FF98());
    fn_801ECEC8(1, 3, 0);
    if (*(float*)(object + 0x40) != lbl_80650A68) {
        *(float*)(object + 0x3C) += *(float*)(object + 0x40);
        fn_8018D2E0(*(float*)(object + 0x3C));
    }
    fn_80226AB4(0x80, 5, count);
    for (j = 0; (u16)j < count; j++) {
        int index = (u16)j;
        fn_80188578(index);
        fn_8018856C(index);
        fn_80188560(index);
    }
    fn_8018855C();
    fn_80226D78(0);
    fn_801ED57C(saved);
}
