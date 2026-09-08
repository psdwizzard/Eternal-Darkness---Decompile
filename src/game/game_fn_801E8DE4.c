typedef unsigned long long u64;
extern unsigned int lbl_8064D5C8;
extern unsigned int lbl_8064D5CC;
extern unsigned int lbl_8064D5D0;
extern unsigned int lbl_8064D5D4;
extern u64 OSGetTime(void);

void fn_801E8DE4(u64 value)
{
    u64 now = OSGetTime();
    lbl_8064D5D4 = (unsigned int)now;
    lbl_8064D5D0 = (unsigned int)(now >> 32);
    lbl_8064D5CC = (unsigned int)value;
    lbl_8064D5C8 = (unsigned int)(value >> 32);
}
