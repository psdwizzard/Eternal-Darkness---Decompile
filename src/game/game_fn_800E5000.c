extern unsigned int rand(void);
#define rand() ((int)rand())

unsigned short fn_800E5000(void)
{
    return rand() % 5;
}
