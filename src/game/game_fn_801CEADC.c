typedef unsigned int u32;

extern void* lbl_806333A0[];
extern void fn_80190508(void*, u32);

void fn_801CEADC(u32 slot, u32 arg1)
{
    void* object = lbl_806333A0[slot];

    if (object != 0) {
        fn_80190508(object, arg1);
        lbl_806333A0[slot] = 0;
    }
}
