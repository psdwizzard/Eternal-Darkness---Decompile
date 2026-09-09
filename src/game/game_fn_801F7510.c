typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lbl_8064D7B8;
extern int lbl_8064D7B4;
extern int lbl_8064D7B0;
extern unsigned int lbl_8064D5A8;
extern const Vec3 lbl_8023B7B4;

extern void fn_801FA748(int, Vec3*);
extern unsigned int fn_800FBFB0(void);
extern void fn_801FA66C(int, int, float);
extern void fn_801F7804(void*);

void fn_801F7510(void* state)
{
    if (lbl_8064D7B8 == 0) {
        Vec3 value = lbl_8023B7B4;
        fn_801FA748(2, &value);
        *(void (**)(void*))((unsigned char*)state + 0x6C) = fn_801F7804;
    } else {
        if ((lbl_8064D5A8 & ((1 << lbl_8064D7B4) - 1)) == 0) {
            unsigned int random = fn_800FBFB0();
            int bits = lbl_8064D7B0;
            unsigned int mask = (1 << bits) - 1;
            int amount;
            bits--;
            mask &= random;
            amount = (1 << bits) - mask;
            fn_801FA66C(2, 0, (float)amount);
        }
        fn_801F7804(state);
        lbl_8064D7B8--;
    }
}
