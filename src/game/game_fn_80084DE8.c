typedef signed short s16;
typedef unsigned int u32;

extern u32 fn_80144710(u32, int, int);
extern u32 fn_8014549C(int, float);
extern void fn_80084404(int, int, float);
extern void fn_80144C40(void);
extern float lbl_8064EA78;

void fn_80084DE8(s16 value, int object)
{
    if ((fn_80144710(0x10000000, 1, 0) == 0 ||
         fn_80144710(0x20000000, 1, 0) != 0) &&
        (fn_8014549C(0, lbl_8064EA78) & 0x30000) == 0) {
        return;
    }

    fn_80084404(object, 0, (float)value);
    fn_80144C40();
}
