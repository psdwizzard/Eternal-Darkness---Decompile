typedef unsigned char u8;
typedef unsigned int u32;

extern u8 lbl_805B6E00[];
extern u32 lbl_8064BA28[];
extern int lbl_8064D120, lbl_8064D14C, lbl_8064D150, lbl_8064D154;
extern int lbl_8064D158, lbl_8064D15C, lbl_8064D180, lbl_8064D184;
extern int lbl_8064D18C, lbl_8064D190, lbl_8064D198;

extern void fn_8015AC74(int);
extern void fn_8015AC84(int);
extern void fn_80158794(void);
extern int fn_800460FC(void);
extern int fn_801E78DC(int);
extern void fn_8021AAA0(void*, int);
extern void fn_8021B6C8(void);
extern void fn_8020D1F0(void*, void*, int);
extern void fn_8020F84C(void*, void*, void*, void*, int, int, int);
extern void fn_8015D1C8(void);
extern void fn_8015A340(void);
extern void fn_8015B800(void);
extern void fn_800BD94C(void);
extern void fn_801E7944(int);
extern void fn_801599BC(int, int);
extern void fn_8015DD48(void);
extern void fn_8015C918(void);
extern void fn_8013816C(void);
extern void fn_8015E794(void);
extern void fn_8020FC0C(void*);

void fn_8015AEB8(int value, int allocation, int flags)
{
    int count;
    int i;
    u8* base = lbl_805B6E00;
    u8* base2 = base + 0x20000;
    u8* base3 = base + 0x30000;

    lbl_8064D14C = value;
    lbl_8064D150 = 0;
    lbl_8064D154 = 0;
    lbl_8064D15C = 0;
    lbl_8064D18C = -1;
    lbl_8064D184 = 0;
    lbl_8064D180 = 0;
    lbl_8064D198 = 0;
    fn_8015AC74(1);
    fn_8015AC84(1);
    fn_80158794();

    if (lbl_8064D120 == 0) {
        count = fn_800460FC();
        lbl_8064D158 = fn_801E78DC(allocation);
        fn_8021AAA0(&lbl_8064D190, 2);
        fn_8021B6C8();
        for (i = 0; i < count; i++) {
        }

        fn_8020D1F0(base2 + 0x4460, base3 - 0x46A4, 0x10);
        fn_8020D1F0(base + 0x268, base3 - 0x4664, 0x10);
        fn_8020D1F0(base3 - 0x4624, base3 - 0x4604, 0x10);
        fn_8020D1F0(base + 0x1FC, base3 - 0x45C4, 0x10);
        fn_8020D1F0(base + 0x248, base3 - 0x4584, 0x10);
        fn_8020D1F0(base3 - 0x4800, base3 - 0x4544, 0x10);
        fn_8020D1F0(base3 - 0x4504, base3 - 0x44E4, 0x10);
        fn_8020D1F0(base3 - 0x44A4, base3 - 0x4484, 0x10);
        fn_8020D1F0(base3 - 0x4444, base3 - 0x4424, 0x10);
        fn_8020D1F0(base2 + 0x4440, base3 - 0x43E4, 0x10);
        fn_8020D1F0(base3 - 0x43A4, base3 - 0x4384, 0x10);
        fn_8020D1F0(base3 - 0x4344, base3 - 0x4324, 0x10);
        fn_8020D1F0(base3 - 0x42E4, base3 - 0x42C4, 0x10);
        fn_8020D1F0(base3 - 0x4284, base3 - 0x4264, 0x10);
        fn_8020D1F0(base3 - 0x4224, base3 - 0x4204, 0x10);

        {
            u8* src0 = base3 - 0x41C4;
            u8* dst0 = base3 - 0x4144;
            u8* src1 = base3 - 0x4104;
            u8* dst1 = base3 - 0x4084;
            u8* src2 = base3 - 0x4044;
            u8* dst2 = base3 - 0x3FC4;
            u8* src3 = base3 - 0x3F84;
            u8* dst3 = base3 - 0x3F04;
            u8* state = base + 0x2A0;
            u8* buffer = base3 - 0x3EC4;
            u8* object = base3 + 0x140;
            for (i = 0; i < 2; i++) {
                fn_8020D1F0(dst0, src0, 0x10);
                fn_8020D1F0(dst1, src1, 0x10);
                fn_8020D1F0(dst2, src2, 0x10);
                fn_8020D1F0(dst3, src3, 0x10);
                *(void**)(state + 0x2060) = dst0;
                *(void**)(state + 0x2064) = dst1;
                *(void**)(state + 0x2068) = dst2;
                *(void**)(state + 0x206C) = dst3;
                fn_8020F84C(object, fn_8015D1C8, state, buffer + 0x2000,
                            0x2000, lbl_8064BA28[i], 1);
                dst0 += 0x20; src0 += 0x40;
                dst1 += 0x20; src1 += 0x40;
                dst2 += 0x20; src2 += 0x40;
                dst3 += 0x20; src3 += 0x40;
                state += 0x20A0; buffer += 0x2000; object += 0x310;
            }
        }
        fn_8020F84C(base3 + 0x760, fn_8015A340, 0, base3 + 0x2A70, 0x2000, 0x1D, 1);
        fn_8020F84C(base3 + 0x2A70, fn_8015B800, 0, base3 + 0x4B80, 0x2000, 0xA, 1);
        fn_8020F84C(base3 + 0x4B80, fn_800BD94C, 0, base3 + 0x6E90, 0x2000, 0x1F, 1);
    } else if ((flags & 2) == 0) {
        fn_801E7944(lbl_8064D158);
    }

    fn_801599BC(lbl_8064D120, flags & 1);
    fn_8015DD48();
    fn_8015C918();
    if (lbl_8064D120 == 0) {
        fn_8013816C();
        fn_8015E794();
        fn_8020FC0C(base3 + 0x760);
        fn_8020FC0C(base3 + 0x2A70);
        for (i = 0; i < 2; i++) {
            fn_8020FC0C(base3 + 0x140 + i * 0x310);
        }
        fn_8020FC0C(base3 + 0x4B80);
        lbl_8064D120 = 1;
    }
}
