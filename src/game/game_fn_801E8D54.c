typedef unsigned long long u64;
typedef unsigned int u32;
extern int lbl_8064D5C0;
extern u32 lbl_8064D5C8;
extern u32 lbl_8064D5CC;
extern u32 lbl_8064D5D0;
extern u32 lbl_8064D5D4;
extern u64 OSGetTime(void);

void fn_801E8D54(void)
{
    /* NonMatching: GC/1.3 reverses the two commutative add operands. */
    if (lbl_8064D5C0 == 0) {
        u64 now = OSGetTime();
        u64 previous = lbl_8064D5D4 | ((u64)lbl_8064D5D0 << 32);
        u64 delta = now - previous;
        u64 accumulator = lbl_8064D5CC | ((u64)lbl_8064D5C8 << 32);
        u64 result = delta + accumulator;
        lbl_8064D5CC = (u32)result;
        lbl_8064D5C8 = result >> 32;
        now = OSGetTime();
        lbl_8064D5D4 = (u32)now;
        lbl_8064D5D0 = now >> 32;
    }
}
