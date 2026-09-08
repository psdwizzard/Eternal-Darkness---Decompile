typedef struct Record16 {
    int a;
    int b;
    int c;
    int d;
} Record16;

extern Record16 lbl_8063BC58[];
extern void fn_80229FA4(int, int, int, int, int);

void fn_801ED494(int index, int a, int b, int c, int d)
{
    if (a != lbl_8063BC58[index].a || b != lbl_8063BC58[index].b ||
        c != lbl_8063BC58[index].c || d != lbl_8063BC58[index].d) {
        lbl_8063BC58[index].a = a;
        lbl_8063BC58[index].b = b;
        lbl_8063BC58[index].c = c;
        lbl_8063BC58[index].d = d;
        fn_80229FA4(index, a, b, c, d);
    }
}
