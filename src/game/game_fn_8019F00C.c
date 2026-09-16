typedef unsigned char u8;
typedef unsigned short u16;

extern void fn_80225F4C(int, void*, int);
extern int fn_8017FFB8(void);
extern int fn_8017FF98(void);
extern int fn_8017FFB0(void);
extern void fn_8022A75C(int, int, int);
extern int* fn_801EF2B0(void);
extern void fn_8022B7CC(int, int, int);
extern void fn_801EDEC4(u16, int, int, int);
extern void fn_80226AB4(int, int, int);
extern void fn_8019F1B0(void);
extern void fn_8019F1B4(u16);
extern void fn_8019F1C0(u16);
extern void fn_8019F1CC(u16);

void fn_8019F00C(void* a, void* b, void* c, void* d, int count)
{
    int first;
    u16 current;
    u16 outer;

    fn_80225F4C(23, d, 48);
    fn_80225F4C(9, a, (u8)fn_8017FFB8());
    fn_80225F4C(11, c, (u8)fn_8017FF98());
    fn_80225F4C(13, b, (u8)fn_8017FFB0());
    fn_8022A75C(1, 3, 0);

    for (outer = 0; outer < count; outer++) {
        int* entries = fn_801EF2B0();
        int index;
        u16 end;

        first = outer * 4;
        fn_8022B7CC(outer, 30, 1);
        for (index = 0; (u16)index < 16; index++) {
            if (entries[(u16)index] == 0) {
                fn_801EDEC4((u16)index, 1, 4, 30);
                break;
            }
        }
        for (index = 0; (u16)index < 16; index++) {
            if (entries[(u16)index] == 5) {
                fn_801EDEC4((u16)index, 1, 4, 30);
                break;
            }
        }
        fn_80226AB4(128, 5, 4);
        end = first + 4;
        first = (u16)first;
        for (; (u16)first < end; first++) {
            current = first;
            fn_8019F1CC(current);
            fn_8019F1C0(current);
            fn_8019F1B4(current);
        }
        fn_8019F1B0();
    }
    fn_8022A75C(1, 3, 1);
}
