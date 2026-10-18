typedef int s32;
typedef float f32;

typedef struct BatchEntry {
    unsigned int words[110];
} BatchEntry;

extern BatchEntry lbl_803028B0[10];
extern void* lbl_8064C4E8;
extern s32 lbl_8064C6EC;
extern s32 lbl_8064CBA4;
extern const f32 lbl_8064DF58;
extern const f32 lbl_8064DF5C;
extern const f32 lbl_8064DF60;
extern const f32 lbl_8064DF64;
extern const f32 lbl_8064DF68;
extern const f32 lbl_8064DF6C;
extern const f32 lbl_8064DF70;

extern s32 fn_801ED3F4(void*);
extern void fn_801A8D38(int);
extern void C_MTXOrtho(void*, f32, f32, f32, f32, f32, f32);
extern void GXSetProjection(void*, s32);
extern void fn_80026320(BatchEntry*);

void fn_8002617C(void)
{
    s32 i;
    s32 token;
    unsigned char first[0x40];
    unsigned char second[0x40];

    if (lbl_8064C6EC != 0) {
        token = fn_801ED3F4(lbl_8064C4E8);
        fn_801A8D38(6);

        if (lbl_8064CBA4 == 1) {
            C_MTXOrtho(first, lbl_8064DF58, lbl_8064DF5C, lbl_8064DF58,
                        lbl_8064DF60, lbl_8064DF64, lbl_8064DF68);
            GXSetProjection(first, 1);
        }

        for (i = 0; i < lbl_8064C6EC; i++) {
            fn_80026320(&lbl_803028B0[i]);
        }

        fn_801ED3F4((void*)token);
        lbl_8064C6EC = 0;

        if (lbl_8064CBA4 == 1) {
            C_MTXOrtho(second, lbl_8064DF58, lbl_8064DF5C, lbl_8064DF6C,
                        lbl_8064DF70, lbl_8064DF64, lbl_8064DF68);
            GXSetProjection(second, 1);
        }
    }
}
