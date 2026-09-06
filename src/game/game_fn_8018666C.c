typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern int lbl_8064D738;
extern u8 lbl_80607120[];

extern void* memcpy(void*, const void*, unsigned long);
extern void DCFlushRange(void*, unsigned long);
extern int fn_801ED57C(int);
extern void fn_8018D0D0(void*, void*, s16);
extern void fn_801ED494(int, int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_801ED510(int, int, int);
extern void fn_80189B70(void*, void*, void*);
extern void fn_801ECC4C(void);

void fn_8018666C(u8* self)
{
    u8* data = lbl_80607120;
    u8 count = self[1];
    u16 size0 = *(u16*)(data + 2);
    int i;
    u16 flush0 = *(u16*)(data + 0xA);
    u16 flush1 = *(u16*)(data + 0xE);
    u16 flush2 = *(u16*)(data + 0xC);
    u8* entries = *(u8**)(self + 0x4C);
    u8* buffer0 = *(u8**)(self + 0x50);
    u8* buffer1 = *(u8**)(self + 0x54);
    u8* buffer2 = *(u8**)(self + 0x58);
    u8* out;
    u8* fill;
    int entry_index;
    int j;
    int saved;

    if (lbl_8064D738 != 0) {
        buffer1 += size0 * 4;
        buffer0 += size0 * 6;
        buffer2 += size0 * 4;
    }

    out = buffer2;
    i = count;
    for (entry_index = 0; entry_index < count; entry_index++) {
        for (j = 0; j < entries[0x20]; j++) {
            out[3] = entries[0x2B];
            out += 4;
        }
        entries += 0x38;
    }

    fill = buffer0 + (i << 1) * 6;
    for (; i < 0x40; i++) {
        memcpy(fill, buffer0, 6);
        memcpy(fill + 6, buffer0 + 6, 6);
        fill += 12;
    }

    DCFlushRange(buffer0, flush0);
    DCFlushRange(buffer1, flush1);
    DCFlushRange(buffer2, flush2);
    saved = fn_801ED57C(0);
    fn_8018D0D0(self, self + 0x5C, *(s16*)(self + 0xE));
    if (self[0x91] & 8) {
        fn_801ED494(3, 0, 0, 0, 3);
        fn_80229C0C(0, 0, 1, 2, 1, 0);
        fn_801ED510(0, 3, 3);
    }
    fn_80189B70(buffer0, buffer1, buffer2);
    fn_801ECC4C();
    fn_801ED57C(saved);
}
