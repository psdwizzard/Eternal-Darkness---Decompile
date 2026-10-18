typedef unsigned int u32;

extern u32 lbl_8064CC88;
extern u32 lbl_8064CC8C;
extern void VIWaitForRetrace(void);
extern int fn_80109198(void*);

int fn_80109AD4(void* state)
{
    lbl_8064CC88 = 0;
    lbl_8064CC8C = 0;
    *(u32*)((unsigned char*)state + 0x17C) = 0;
    while (fn_80109198(state) != 0) {
        VIWaitForRetrace();
    }
}
