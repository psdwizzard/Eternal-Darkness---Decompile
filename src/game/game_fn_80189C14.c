typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef struct Vec3 { float x, y, z; } Vec3;

extern int lbl_8064D738;
extern u8 lbl_80607120[], lbl_8063C098[];
extern void fn_80188A7C(void*, void*, void*), fn_8018D020(void);
extern void fn_8017ACE0(void*, Vec3*, Vec3*), DCFlushRange(void*, unsigned long);
extern void fn_80188584(void*, void*), fn_8018D0D0(void*, void*, s16);
extern int fn_801ED57C(int);
extern void fn_801889D8(void*, void*, void*), fn_80226D78(int);

void fn_80189C14(u8* arg)
{
    u8* data = lbl_80607120;
    int entry_index;
    int j;
    u8 count;
    u16 size0 = *(u16*)(data + 2);
    u16 flush0;
    u16 flush1;
    u16 flush2;
    u8* entries;
    u8* buffer0;
    s16* position;
    u8* buffer1;
    u8* buffer2;
    u8* out;
    u8* self;
    int position_offset;
    int saved;

    self = arg;
    count = self[1];
    flush0 = *(u16*)(data + 0xA);
    flush1 = *(u16*)(data + 0xE);
    flush2 = *(u16*)(data + 0xC);
    buffer0 = *(u8**)(self + 0x50);
    buffer1 = *(u8**)(self + 0x54);
    buffer2 = *(u8**)(self + 0x58);
    if (lbl_8064D738 != 0) {
        buffer1 += size0 * 4;
        buffer0 += size0 * 6;
        buffer2 += size0 * 4;
    }
    entries = *(u8**)(self + 0x4C);
    out = buffer2;
    position_offset = 0;
    for (entry_index = 0; entry_index < count; entry_index++) {
        position = (s16*)(buffer0 + position_offset);
        fn_80188A7C(entries, position, fn_8018D020);
        for (j = 0; j < entries[0x20]; j++) {
            Vec3 output;
            Vec3 input;
            input.x = (float)position[0];
            input.y = (float)position[1];
            input.z = (float)position[2];
            fn_8017ACE0(lbl_8063C098, &input, &output);
            position[0] = (s16)output.x;
            position[1] = (s16)output.y;
            position[2] = (s16)output.z;
            position += 3;
            out[3] = entries[0x2B];
            out += 4;
        }
        entries += 0x38;
        position_offset += 0x18;
    }
    *(s16*)(buffer0 + 0x00) += 0x32;
    *(s16*)(buffer0 + 0x02) += 0x32;
    *(s16*)(buffer0 + 0x06) -= 0x32;
    *(s16*)(buffer0 + 0x08) -= 0x32;
    *(s16*)(buffer0 + 0x0C) -= 0x32;
    *(s16*)(buffer0 + 0x0E) -= 0x32;
    *(s16*)(buffer0 + 0x12) += 0x32;
    *(s16*)(buffer0 + 0x14) += 0x32;
    DCFlushRange(buffer0, flush0);
    DCFlushRange(buffer1, flush1);
    DCFlushRange(buffer2, flush2);
    fn_80188584(self + 0x94, self + 0xB8);
    saved = fn_801ED57C(0);
    fn_8018D0D0(self, self + 0x5C, *(s16*)(self + 0xE));
    fn_801889D8(buffer0, buffer1, buffer2);
    fn_801ED57C(saved);
    fn_80226D78(0);
}
