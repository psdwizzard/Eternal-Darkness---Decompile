typedef struct Pending {
    int first;
    int second;
    int third;
    int pad;
} Pending;

extern int lbl_8064D070;
extern Pending lbl_805B43F0;
extern void srand(unsigned int);

void fn_80144EE0(int first, int second)
{
    if (lbl_8064D070 == 0) {
        srand(0);
        lbl_8064D070 = -1;
        lbl_805B43F0.third = first;
        lbl_805B43F0.second = 0;
        lbl_805B43F0.first = second;
    }
}
