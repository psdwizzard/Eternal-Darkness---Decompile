typedef int s32;
typedef unsigned int u32;

typedef struct GameState {
    unsigned char unk_00[0x1C];
    u32 count;
    unsigned char unk_20[8];
    unsigned char data[0xC];
} GameState;

extern s32 lbl_8064CDC4;
extern s32 lbl_8064C5A4;
extern s32 lbl_8064C59C;
extern void* lbl_8064C5A0;
extern void* lbl_8064D68C;
extern void* lbl_8064C4E0;
extern GameState lbl_80301D08;

extern void GXSetPixelFmt(s32, s32);
extern void fn_8011E174(s32, s32);
extern void fn_8011DFA8(void);
extern void fn_8016B400(int, int, int);
extern int fn_80201B44();
extern void fn_801D0D30(void);
extern void* memcpy(void*, const void*, u32);
extern void srand(s32);
extern void fn_80144EE0(void*, u32);
extern void fn_80144E78(void*, u32);
extern void fn_801EBA58(void*);
extern int fn_801E79FC(void*, int);
extern void *fn_80201814();
extern void fn_80201F80(void*, s32, s32);

static inline u32 max_u32(u32 a, u32 b)
{
    return a > b ? a : b;
}

void fn_800082A4(void)
{
    void* object;
    s32 i;
    u32 value;

    GXSetPixelFmt(1, 0);
    fn_8011E174(0x10, 0);
    fn_8011DFA8();

    if (lbl_8064CDC4 > 0) {
        value = lbl_8064CDC4;
        lbl_8064CDC4 = 0;
        fn_8016B400(value, 0, 0);
    }

    if (lbl_8064C5A4 > 0) {
        if (lbl_8064C5A4 != 0x8C3) {
            fn_80201B44();
            fn_801D0D30();
        }
        fn_8016B400(lbl_8064C5A4, 0, 0);
        lbl_8064C5A4 = 0;
    } else if (lbl_8064C59C == 2) {
        memcpy(&lbl_80301D08, lbl_8064C5A0, 0x34);
        lbl_80301D08.count =
            lbl_80301D08.count < 1 ? lbl_80301D08.count : 1;
        srand(0);
        for (i = 0; i < 1000; i++) {
        }
        fn_80144EE0(lbl_80301D08.data, lbl_80301D08.count);
    } else if (lbl_8064C59C == 1) {
        lbl_80301D08.count =
            max_u32((lbl_80301D08.count = 0x1C1F), 1);
        srand(0);
        for (i = 0; i < 1000; i++) {
        }
        fn_80144E78(lbl_80301D08.data, lbl_80301D08.count);
    }

    fn_801EBA58(lbl_8064D68C);
    if (fn_801E79FC(lbl_8064C4E0, 0xD) != 0) {
        object = fn_80201814(fn_80201B44());
        if (object != 0) {
            fn_80201F80(object, 1, 0x33800);
        }
    }
}
