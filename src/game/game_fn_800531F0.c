typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct TransitionState {
    u8 pad000[0x1C8];
    s32 elapsed;
    u8 pad1CC[6];
    s16 room;
    u8 pad1D4[2];
    s16 resource;
    s8 action;
    u8 selected;
    u8 type;
    u8 next_type;
    s8 special;
    u8 pad1DD;
    u8 pending;
    u8 pad1DF;
    u8 descriptor_flag;
    u8 pad1E1[2];
    u8 busy;
    u8 restore;
    u8 mode;
    u8 effect;
} TransitionState;

typedef struct TransitionDescriptor {
    u8 pad00[8];
    s32 room;
    s32 effect;
    u8 pad10[9];
    u8 mode;
    s8 requirement;
    u8 pad1B[3];
    s16 resource;
    u8 pad20[8];
} TransitionDescriptor;

typedef struct GameState {
    void* object;
    u8 pad004[0x1910];
    u8 active;
} GameState;

extern TransitionState lbl_8030F540;
extern TransitionDescriptor lbl_80241DE8[];
extern GameState lbl_803003C8;
extern void* lbl_8064C4E0;
extern void* lbl_8064C4E4;
extern void* lbl_8064C85C;
extern void* lbl_8064C8EC;
extern s32 lbl_8064C84C;
extern u32 lbl_8064B998;
extern s32 lbl_8064C850;
extern s32 lbl_8064D18C;
extern s32 lbl_8064B810;
extern s32 lbl_8064E498;
extern float lbl_8064E4CC;
extern char lbl_8064B4D0;
extern u8 lbl_80243970[];

extern s32 fn_80052900(void);
extern void* fn_8011FCE4(void*);
extern void fn_80008710(void*, void*);
extern u32* fn_801E5D20(void*);
extern void fn_801E6228(void*, const char*, ...);
extern void fn_80120AD0(void*, s32, s32, s32, float, float);
extern void* fn_80144628(s32, void*, s32);
extern void fn_80042DA8(void);
extern void fn_80200FC0(s32, s32, s32, float);
extern void* fn_80201ADC(void);
extern void fn_80042974(void);
extern void fn_80042A64(void);
extern void *fn_80201BC8();
extern void* fn_8011F950(void*);
extern void fn_8012BA28(void*);
extern void fn_801F5980(void);
extern void fn_8015AC74(s32);
extern void fn_800AFEC0(void);
extern void fn_800E45C8(void);
extern void fn_8015977C(s32, s32, s32, s32, s32);
extern void fn_8015AD00(s32);
extern void fn_8015AC84(s32);
extern void fn_8001D9FC(s32);
extern void fn_801ACC94(s32);
extern void fn_801AC350(s32, s32, s32);
extern void fn_801B0D30(void);
extern void fn_80237D2C(s32);
extern void fn_8015DD94(s32);
extern s32 fn_8004736C(s32);
extern s32 fn_801EF38C(s32);
extern void fn_80144430(s32, s32);
extern void fn_801E79A0(void*, s32);
extern void fn_801A9964(s32);
extern void fn_801B2348(s32);
extern void fn_801ACD8C(void);
extern void fn_801AD404(s32, s32, s32);
extern void fn_801AD490(void);
extern void* fn_801B09DC(void*);
extern void* fn_800E4594(s32);
extern void fn_802367B0(void*, void*);
extern void fn_80054700(void);
extern void fn_80048620(s32);
extern int fn_80201B44();
extern void fn_801D0D30(void);
extern void fn_80046C98(s32);

void fn_800531F0(void)
{
    void* object;
    lbl_8030F540.busy = 0;
    if (fn_80052900() != 0) {
        return;
    }
    if (lbl_8064C4E4 != 0) {
        fn_80008710(lbl_803003C8.object, fn_8011FCE4(lbl_8064C4E4));
    }
    if (lbl_8064C8EC != 0) {
        u32* flags = fn_801E5D20(lbl_8064C8EC);
        *flags &= ~1u;
        fn_801E6228(lbl_8064C8EC, &lbl_8064B4D0);
    }
    fn_80120AD0(lbl_8064C4E4, 0, 0, 0, lbl_8064E4CC, lbl_8064E4CC);
    lbl_8064C85C = fn_80144628(2, lbl_80243970, 0);
    fn_80042DA8();
    fn_80200FC0(0x59, -1, 0, lbl_8064E4CC);

    if (lbl_80241DE8[lbl_8030F540.type].resource != -1 &&
        lbl_803003C8.active != 0 && lbl_8030F540.special == 0) {
        if (lbl_8030F540.type != 0x49 && lbl_8030F540.type != 0x4A &&
            lbl_8030F540.type != 0x4B) {
            object = fn_80201ADC();
            fn_80042974();
            fn_80042A64();
            if (object != 0) {
                object = fn_80201BC8(object);
                if (object != 0 && fn_8011F950(object) != 0) {
                    fn_8012BA28(fn_8011F950(object));
                }
            }
        }
        if (lbl_8030F540.type == 0x4C || lbl_8030F540.type == 0x4D ||
            lbl_8030F540.type == 0x4E) {
            fn_801F5980();
        }
    }

    fn_8015AC74(0);
    if (lbl_8030F540.room == 0 && lbl_8030F540.special != 0) {
        fn_800AFEC0();
        lbl_8030F540.room = (s16)lbl_8064D18C;
    }
    fn_800E45C8();
    if (lbl_80241DE8[lbl_8030F540.type].room != -1) {
        if (lbl_8064D18C != lbl_80241DE8[lbl_8030F540.type].room) {
            fn_8015977C(lbl_80241DE8[lbl_8030F540.type].room, -2, 0, 0, 0x80);
        } else if (lbl_8030F540.special != 0) {
            fn_8015AD00(2);
        }
    } else {
        fn_8015AD00(2);
        lbl_8064B810 = 0;
    }
    fn_8015AC84(0);
    fn_8001D9FC(6);
    fn_801ACC94(0);
    fn_801AC350(0, 0, 1);
    fn_801B0D30();
    fn_80237D2C(1);
    fn_8015DD94(lbl_8030F540.type);
    lbl_8030F540.mode = (u8)fn_8004736C(0);
    lbl_8030F540.effect = (u8)fn_801EF38C(0);
    fn_80144430(2, 1);
    if (lbl_8030F540.effect != 0) {
        fn_801E79A0(lbl_8064C4E0, 0x2ED);
        if (lbl_8064B998 != (u32)-1) {
            fn_801A9964(lbl_8064B998);
            lbl_8064B998 = -1;
        }
    }
    fn_801B2348(1);
    fn_801ACD8C();
    fn_801AD404(0, 0, 10);
    fn_801AD490();
    fn_801AD404(100, 100, 1);

    if (lbl_80241DE8[lbl_8030F540.type].effect != -1 &&
        lbl_80241DE8[lbl_8030F540.type].effect != 60) {
        u32 value;
        void* timer = fn_801B09DC(&value);
        fn_802367B0(fn_800E4594(lbl_80241DE8[lbl_8030F540.type].effect), timer);
    }
    lbl_8064C84C = 0;
    lbl_8030F540.busy = 0;
    lbl_8030F540.next_type = 0;
    lbl_8030F540.resource = 0;
    lbl_8030F540.pad1DF = 0;
    lbl_8030F540.pending = 0;
    lbl_8030F540.action = -1;
    lbl_8030F540.restore = 0;
    lbl_8030F540.selected = 0;
    fn_80054700();
    if (lbl_8030F540.special != 0) {
        fn_80048620(1);
        fn_80201B44();
        fn_801D0D30();
    }
    {
        u8 type = lbl_8030F540.type;
        TransitionDescriptor* final_descriptor = &lbl_80241DE8[type];
        lbl_8064C850 = 0;
        lbl_8030F540.descriptor_flag = final_descriptor->mode;
    }
    fn_80046C98(0);
}
