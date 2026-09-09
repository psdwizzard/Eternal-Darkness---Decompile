typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lbl_8064D7B8;
extern int lbl_8064D7B4;
extern int lbl_8064D7B0;
extern unsigned int lbl_8064D5A8;
extern const Vec3 lbl_8023B7CC;

extern unsigned int fn_800FBFB0(void);
extern void fn_801441C0(unsigned short, unsigned short, unsigned short);
extern void fn_801FA66C(int, int, float);
extern void fn_801FA748(int, Vec3*);
extern void fn_801F7804(void*);

void fn_801F76EC(void* state)
{
    unsigned int random;
    unsigned int mask;
    int selected;
    int bits;

    if ((lbl_8064D5A8 & ((1 << lbl_8064D7B4) - 1)) == 0) {
        random = fn_800FBFB0();
        bits = lbl_8064D7B0;
        mask = (1 << bits) - 1;
        bits--;
        selected = mask & random;
        fn_801FA66C(3, 0, (float)((1 << bits) - selected));
        fn_801441C0((unsigned short)((int)selected >> 1),
                    (unsigned short)lbl_8064D7B0,
                    (unsigned short)((1 << lbl_8064D7B4) - 1));
    }

    fn_801F7804(state);

    if (lbl_8064D7B8 == 0) {
        Vec3 value = lbl_8023B7CC;
        fn_801FA748(3, &value);
        *(void (**)(void*))((unsigned char*)state + 0x6C) = fn_801F7804;
    }

    lbl_8064D7B8--;
}
