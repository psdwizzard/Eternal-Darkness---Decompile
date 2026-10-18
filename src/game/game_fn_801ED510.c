typedef struct Record8 {
    int a;
    int b;
} Record8;

extern Record8 lbl_8063BB18[];
extern void GXSetTevSwapMode(int, int, int);

void fn_801ED510(int index, int a, int b)
{
    if (a != lbl_8063BB18[index].a || b != lbl_8063BB18[index].b) {
        lbl_8063BB18[index].a = a;
        lbl_8063BB18[index].b = b;
        GXSetTevSwapMode(index, a, b);
    }
}
