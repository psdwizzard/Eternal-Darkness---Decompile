typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct TransitionState {
    u8 pad00[0x1D8];
    s8 countdown;
    u8 pad1D9;
    u8 type;
    u8 pad1DB[9];
    s8 active;
} TransitionState;

typedef struct TypeDescriptor {
    u8 pad00[0x10];
    s16 action;
    u8 pad12[6];
} TypeDescriptor;

extern TransitionState lbl_8030F540;
extern TypeDescriptor lbl_802417D0[];
extern void* lbl_8064C85C;
extern s32 lbl_8064CC20;
extern void fn_80045A24(s32, s32);
extern void fn_80052CC0(s32, s32);
extern void fn_80144C4C(void*);
extern s32 fn_800EE8F8(void);
extern u32 GXReadDrawSync(void);
extern void fn_8005251C(s32, s32);
extern void fn_800B9474(s32);

void fn_80052BBC(void)
{
    if (lbl_8030F540.active == 1) {
        s16 action = lbl_802417D0[lbl_8030F540.type].action;
        if (action == -1) {
            lbl_8030F540.active = 0;
            fn_80045A24(0, 0);
        } else if (action == 1) {
            fn_80052CC0(0, 0);
            return;
        }
    }

    fn_80144C4C(lbl_8064C85C);
    if (lbl_8064CC20 == 0 || fn_800EE8F8() == 0) {
        fn_80052CC0(0, 0);
    }

    if (lbl_8030F540.countdown != -1) {
        if (lbl_8030F540.countdown == 0) {
            lbl_8030F540.countdown = -1;
            while ((GXReadDrawSync() & 0xFFFF) != 0xBEEF) {}
            fn_8005251C(0, 0);
        } else {
            lbl_8030F540.countdown--;
        }
    }
    fn_800B9474(0x7F);
}
