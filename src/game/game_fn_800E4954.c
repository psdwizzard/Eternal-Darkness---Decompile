extern unsigned int rand(void);
#define rand() ((int)rand())
extern unsigned short lbl_8064B7E4[2];

unsigned short fn_800E4954(void)
{
    return lbl_8064B7E4[rand() & 1];
}
