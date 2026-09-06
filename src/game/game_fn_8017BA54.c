typedef unsigned long long u64;

extern unsigned int lbl_8064D200;
extern unsigned int lbl_8064D204;

void fn_8017BA54(u64 value)
{
    lbl_8064D204 = (unsigned int)value;
    lbl_8064D200 = (unsigned int)(value >> 32);
}
