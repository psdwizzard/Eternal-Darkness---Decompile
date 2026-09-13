typedef unsigned char u8;

extern u8 lbl_8064D29C;
extern u8 lbl_8064D29D;

extern void fn_801B8FE4(u8, int, int, int);
extern void fn_801AD8B4(void);
extern void fn_801AECAC(void);

#define MAX0(x) ((x) > 0 ? (x) : 0)
#define CLAMP127(x) (MAX0(x) > 127 ? 127 : MAX0(x))

void fn_801A9A40(int arg0, int left, int right)
{
    if (left != -1) {
        u8 level = CLAMP127(left);
        lbl_8064D29D = level;
        fn_801B8FE4(level, arg0, 1, 0);
        fn_801AD8B4();
    }
    if (right != -1) {
        u8 level = CLAMP127(right);
        lbl_8064D29C = level;
        fn_801B8FE4(level, arg0, 0, 1);
        fn_801AECAC();
    }
}
