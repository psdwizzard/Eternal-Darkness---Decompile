extern unsigned int rand(void);
#define rand() ((int)rand())
extern int lbl_8064B7D0;
extern unsigned short *lbl_8064CAE4;

#pragma opt_propagation off
unsigned short fn_800E4918(void)
{
    int value = rand();
    unsigned short *table = lbl_8064CAE4;
    int count = lbl_8064B7D0;
    return table[(unsigned short)(value % count)];
}
#pragma opt_propagation reset
